//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP server, coroutine
//
//------------------------------------------------------------------------------

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/url.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include "handler.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace urls = boost::urls;           // from <boost/url.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


//------------------------------------------------------------------------------

// Report a failure
    void
fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}


// Handles an HTTP server connection
    void
do_session(
        beast::tcp_stream& stream,
        std::shared_ptr<std::string const> const& doc_root,
        net::yield_context yield)
{
    beast::error_code ec;

    // This buffer is required to persist across reads
    beast::flat_buffer buffer;

    // This lambda is used to send messages
    for(;;)
    {
        // Set the timeout.
        stream.expires_after(std::chrono::seconds(30));

        // Read a request
        http::request<http::string_body> req;
        http::async_read(stream, buffer, req, yield[ec]);
        if(ec == http::error::end_of_stream)
            break;
        if(ec)
            return fail(ec, "read");

        request_handler handler(*doc_root, std::move(req));
        http::message_generator msg = handler.response();

        // Determine if we should close the connection
        bool keep_alive = msg.keep_alive();

        // Send the response
        beast::async_write(stream, std::move(msg), yield[ec]);

        if(ec)
            return fail(ec, "write");

        if(! keep_alive)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            break;
        }
    }

    // Send a TCP shutdown
    stream.socket().shutdown(tcp::socket::shutdown_send, ec);

    // At this point the connection is closed gracefully
}

//------------------------------------------------------------------------------

// Accepts incoming connections and launches the sessions
    void
do_listen(
        net::io_context& ioc,
        tcp::endpoint endpoint,
        std::shared_ptr<std::string const> const& doc_root,
        net::yield_context yield)
{
    beast::error_code ec;

    // Open the acceptor
    tcp::acceptor acceptor(ioc);
    acceptor.open(endpoint.protocol(), ec);
    if(ec)
        return fail(ec, "open");

    // Allow address reuse
    acceptor.set_option(net::socket_base::reuse_address(true), ec);
    if(ec)
        return fail(ec, "set_option");

    // Bind to the server address
    acceptor.bind(endpoint, ec);
    if(ec)
        return fail(ec, "bind");

    // Start listening for connections
    acceptor.listen(net::socket_base::max_listen_connections, ec);
    if(ec)
        return fail(ec, "listen");

    for(;;)
    {
        tcp::socket socket(ioc);
        acceptor.async_accept(socket, yield[ec]);
        if(ec)
            fail(ec, "accept");
        else
            boost::asio::spawn(
                    acceptor.get_executor(),
                    std::bind(
                        &do_session,
                        beast::tcp_stream(std::move(socket)),
                        doc_root,
                        std::placeholders::_1)
                    );
    }
}

int main(int argc, char* argv[])
{
    // Check command line arguments.
    if (argc != 1)
    {
        std::cerr <<
            "Usage: movepoint <address> <port> <doc_root> <threads>\n" <<
            "Example:\n" <<
            "    movepoint 0.0.0.0 8080\n";
        return EXIT_FAILURE;
    }
    auto const address = net::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(std::atoi("8080"));
    auto const doc_root = std::make_shared<std::string>("/var/www/movepoint.ru/");
    auto const threads = 4;

    // The io_context is required for all I/O
    net::io_context ioc{threads};

    auto listen = std::bind(
                &do_listen,
                std::ref(ioc),
                tcp::endpoint{address, port},
                doc_root,
                std::placeholders::_1);

    auto handler = [](std::exception_ptr ex)
            {
                // if an exception occurred in the coroutine,
                // it's something critical, e.g. out of memory
                // we capture normal errors in the ec
                // so we just rethrow the exception here,
                // which will cause `ioc.run()` to throw
                if (ex) {
                    std::cerr << "EXC" << std::endl;
                    std::rethrow_exception(ex);
                }
            };

    // Spawn a listening port
    boost::asio::spawn(ioc, listen, handler);

    auto run = [&ioc]
                {
                try
		{
			ioc.run();
		} catch (const std::exception &ex) {
			std::cerr << ex.what() << std::endl;
		}
                };
    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for(auto i = threads - 1; i > 0; --i)
        v.emplace_back(run);
    run();

    return EXIT_SUCCESS;
}
