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

// Return a reasonable mime type based on the extension of a file.
beast::string_view
mime_type(beast::string_view path)
{
    using beast::iequals;
    auto const ext = [&path]
    {
        auto const pos = path.rfind(".");
        if(pos == beast::string_view::npos)
            return beast::string_view{};
        return path.substr(pos);
    }();
    if(iequals(ext, ".htm"))  return "text/html";
    if(iequals(ext, ".html")) return "text/html";
    if(iequals(ext, ".php"))  return "text/html";
    if(iequals(ext, ".css"))  return "text/css";
    if(iequals(ext, ".txt"))  return "text/plain";
    if(iequals(ext, ".js"))   return "application/javascript";
    if(iequals(ext, ".json")) return "application/json";
    if(iequals(ext, ".xml"))  return "application/xml";
    if(iequals(ext, ".swf"))  return "application/x-shockwave-flash";
    if(iequals(ext, ".flv"))  return "video/x-flv";
    if(iequals(ext, ".png"))  return "image/png";
    if(iequals(ext, ".jpe"))  return "image/jpeg";
    if(iequals(ext, ".jpeg")) return "image/jpeg";
    if(iequals(ext, ".jpg"))  return "image/jpeg";
    if(iequals(ext, ".gif"))  return "image/gif";
    if(iequals(ext, ".bmp"))  return "image/bmp";
    if(iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
    if(iequals(ext, ".tiff")) return "image/tiff";
    if(iequals(ext, ".tif"))  return "image/tiff";
    if(iequals(ext, ".svg"))  return "image/svg+xml";
    if(iequals(ext, ".svgz")) return "image/svg+xml";
    return "application/text";
}

// Append an HTTP rel-path to a local filesystem path.
// The returned path is normalized for the platform.
std::string
path_cat(
        beast::string_view base,
        beast::string_view path)
{
    if(base.empty())
        return std::string(path);
    std::string result(base);
    char constexpr path_separator = '/';
    if(result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
    return result;
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
    res.set(http::field::content_type, mime_type(target));
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
        return get_root();
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

    // Build the path to the requested file
    std::string path = path_cat(doc_root, target);
    if(request.target().back() == '/')
        path.append("index.html");

    // Body to be returned
    http::file_body::value_type body;

    // Attempt to open the file
    beast::error_code ec;
    body.open(path.c_str(), beast::file_mode::scan, ec);

    // Handle the case where the file doesn't exist
    if(ec == beast::errc::no_such_file_or_directory)
        return not_found(request.target());

    // Handle an unknown error
    if(ec)
        return server_error(ec.message());

    // Cache the size since we need it after the move
    auto const size = body.size();

    // Respond to HEAD request
    if(request.method() == http::verb::head)
    {
        http::response<http::empty_body> res{http::status::ok, request.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, mime_type(path));
        res.content_length(size);
        res.keep_alive(request.keep_alive());
        return res;
    }

    // Respond to GET request
    http::response<http::file_body> res{
        std::piecewise_construct,
            std::make_tuple(std::move(body)),
            std::make_tuple(http::status::ok, request.version())};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime_type(path));
    res.content_length(size);
    res.keep_alive(request.keep_alive());
    return res;
}
