#include <boost/url.hpp>
#include "handler.h"
#include "index.h"
#include "season.h"
#include "comments.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace urls = boost::urls;           // from <boost/url.hpp>

using message_generator = http::message_generator;

request_handler::request_handler(const std::string &root, request_type &&req)
    : doc_root(root),
    request(req)
{
}

message_generator request_handler::bad_request(beast::string_view why)
{
    http::response<http::string_body> res{http::status::bad_request, request.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(request.keep_alive());
    res.body() = std::string(why);
    res.prepare_payload();
    return res;
};

// Returns a not found response
message_generator request_handler::not_found(beast::string_view target)
{
    http::response<http::string_body> res{http::status::not_found, request.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(request.keep_alive());
    res.body() = "The resource '" + std::string(target) + "' was not found.";
    res.prepare_payload();
    return res;
};

message_generator request_handler::server_error(beast::string_view what)
{
    http::response<http::string_body> res{http::status::internal_server_error, request.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(request.keep_alive());
    res.body() = "An error occurred: '" + std::string(what) + "'";
    res.prepare_payload();
    return res;
};

message_generator request_handler::empty_body(beast::string_view target)
{
    http::response<http::empty_body> res{http::status::ok, request.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.keep_alive(request.keep_alive());
    return res;
}

message_generator request_handler::get_root()
{
    static Index index;
    std::string body;
    try {
        body = std::move(index.content());
    } catch (std::exception &exc) {
        return server_error(exc.what());
    }

    http::response<http::string_body> res;
    res.result(http::status::ok);
    res.version(request.version());
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.body() = body;
    res.content_length(body.size());
    res.keep_alive(request.keep_alive());
    return res;
}

message_generator request_handler::post_root()
{
    std::string nickname;
    std::string text;

    auto request_body = request.body();
    auto url="http://post.data/?" + request_body;
    urls::url_view uv(url);
    auto pv = uv.params();
    for (auto p : pv) {
        if (p.key == "nickname")
            nickname = p.value;
        else if (p.key == "text")
            text = p.value;
    }

    if (nickname.empty() || nickname.find('\n') != std::string::npos)
        return bad_request("Invalid nickname");

    try {
        static Comments comments;
        comments.add(nickname, text);

        std::string body = "you successfully posted";
        http::response<http::string_body> res;
        res.result(http::status::see_other);
        res.version(request.version());
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.set(http::field::location, "/");
        res.body() = body;
        res.content_length(body.size());
        res.keep_alive(request.keep_alive());
        return res;
    } catch (std::exception &exc) {
        return server_error(exc.what());
    }
}

message_generator request_handler::get_season(const std::string &key)
{
    Season season(key);
    std::string body(season.content());

    http::response<http::string_body> res;
    res.result(http::status::ok);
    res.version(request.version());
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.body() = body;
    res.content_length(body.size());
    res.keep_alive(request.keep_alive());
    return res;
}

message_generator request_handler::response()
{
    auto target = request.target();
    auto method = request.method();
    auto fields = request.base();
    auto forwarded = fields[http::field::forwarded];
    auto cookie = std::string(fields[http::field::cookie]);

    if (method != http::verb::get &&
        method != http::verb::head &&
        method != http::verb::post)
        return bad_request("Unknown HTTP-method");

    if (target.empty() || target[0] != '/' ||
        target.find("..") != beast::string_view::npos)
        return bad_request("Illegal request-target");

    
    std::cerr << request.method() << " " << target << " " << forwarded << std::endl;

    if (target == "/" && method == http::verb::get) {
        return get_root();
    } else if (target == "/" && method == http::verb::post) {
        return post_root();
    }

    if (target == "/season1.html" && method == http::verb::get) {
        return get_season("season1");
    } else if (target == "/season1.html" && method == http::verb::post) {
        return empty_body(target);
    }

    if (target == "/season2.html" && method == http::verb::get) {
        return get_season("season2");
    } else if (target == "/season2.html" && method == http::verb::post) {
        return empty_body(target);
    }

    if (target == "/season3.html" && method == http::verb::get) {
        return get_season("season3");
    } else if (target == "/season3.html" && method == http::verb::post) {
        return empty_body(target);
    }

    if (target == "/season4.html" && method == http::verb::get) {
        return get_season("season4");
    } else if (target == "/season4.html" && method == http::verb::post) {
        return empty_body(target);
    }

    return not_found(request.target());
}
