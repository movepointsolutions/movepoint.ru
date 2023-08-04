#include <sstream>
#include <string>
#include <boost/url.hpp>
#include <mimetic/mimetic.h>
#include "handler.h"
#include "index.h"
#include "redis.h"
#include "season.h"
#include "login.h"
#include "comments.h"
#include "session_manager.h"
#include "form_part.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace urls = boost::urls;           // from <boost/url.hpp>

using message_generator = http::message_generator;

using namespace std::string_literals;

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
    std::cerr << "SERVER_ERROR " << std::string(what) << std::endl;
    res.prepare_payload();
    return res;
};

message_generator request_handler::empty_body()
{
    http::response<http::empty_body> res{http::status::ok, request.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.keep_alive(request.keep_alive());
    return res;
}

message_generator request_handler::wiki()
{
    http::response<http::empty_body> res{http::status::see_other, request.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    const auto wiki_link = "https://wikireality.ru/wiki/Lina_the_Dark_Elf";
    res.set(http::field::location, wiki_link);
    res.keep_alive(request.keep_alive());
    return res;
}

message_generator request_handler::login(long long session)
{
    static Login login;
    std::string body;
    try {
        body = std::move(login.content());
    } catch (std::exception &exc) {
        return server_error(exc.what());
    }

    http::response<http::string_body> res;
    res.result(http::status::ok);
    res.version(request.version());
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    if (session < 0) {
        static Redis redis;
        std::ostringstream cookie1, cookie2;
        std::pair<long long, std::string> session{redis.new_session()};
        cookie1 << "session=" << session.first;
        cookie2 << "session_hash=" << session.second;
        std::cerr << "Set " << cookie1.str() << std::endl;
        res.set(http::field::set_cookie, cookie1.str());
        res.insert(http::field::set_cookie, cookie2.str());
    }
    res.body() = body;
    res.content_length(body.size());
    res.keep_alive(request.keep_alive());
    return res;
}

message_generator request_handler::post_login(long long session)
{
    std::string login;
    std::string password;

    auto request_body = request.body();
    auto url="http://post.data/?" + request_body;
    urls::url_view uv(url);
    auto pv = uv.params();
    for (auto p : pv) {
        if (p.key == "login")
            login = p.value;
        else if (p.key == "password")
            password = p.value;
    }

    if (login.empty() || login.find('\n') != std::string::npos || login.size() > 16)
        return bad_request("Invalid login");

    if (password.empty() || password.find('\n') != std::string::npos || password.size() > 16)
        return bad_request("Invalid password");

    try {
        static session_manager sm;
        auto ph = sm.get_passwordhash(password);
        static Redis redis;
        auto vph = redis.password_hash(login);
        std::cerr << "LOGIN" << login << ":" << ph << ":" << vph << std::endl;
        if (ph != vph)
            return bad_request("Login and password don't match");
        redis.login_session(session, login);

        std::string body = "you successfully logged in";
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

message_generator request_handler::get_root(long long session)
{
    static Redis redis;
    Index index{redis.session_login(session)};
    std::string body;
    try {
        body = std::move(index.content(session));
    } catch (std::exception &exc) {
        return server_error(exc.what());
    }

    http::response<http::string_body> res;
    res.result(http::status::ok);
    res.version(request.version());
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    if (session < 0) {
        std::ostringstream cookie1, cookie2;
        std::pair<long long, std::string> session{redis.new_session()};
        cookie1 << "session=" << session.first;
        cookie2 << "session_hash=" << session.second;
        std::cerr << "Set " << cookie1.str() << std::endl;
        res.set(http::field::set_cookie, cookie1.str());
        res.insert(http::field::set_cookie, cookie2.str());
    }
    res.body() = body;
    res.content_length(body.size());
    res.keep_alive(request.keep_alive());
    return res;
}

message_generator request_handler::post_root(long long session)
{
    auto request_body = request.body();
    std::string nickname;
    std::string text;
    std::string file;

    std::string content_type = request.base()[http::field::content_type];
    const auto multipart = "multipart/form-data"s;
    if (content_type == "application/x-www-form-urlencoded") {
        auto url="http://post.data/?" + request_body;
        urls::url_view uv(url);
        auto pv = uv.params();
        for (auto p : pv) {
            if (p.key == "nickname")
                nickname = p.value;
            else if (p.key == "text")
                text = p.value;
            else if (p.key == "file")
                file = p.value;
        }
    } else if (content_type.starts_with(multipart)) {
        std::string msg = "From: Movepoint <internal@movepoint.ru>\r\n";
        for (const auto &f : request.base()) {
            msg += f.name_string();
            msg += ": "s;
            msg += f.value();
            msg += "\r\n";
        }
        msg += "\r\n" + request_body;

        mimetic::MimeEntity entity;
        entity.load(msg.begin(), msg.end());
        const auto parts = entity.body().parts();
        for (const auto &p : parts) {
            const auto cd = p->header().contentDisposition();
            assert(cd.type() == "form-data");
            std::cerr << cd << std::endl;
            const std::string name = cd.param("name");
            std::ostringstream O;
            O << p->body();
            const std::string value = O.str();
            if (name == "nickname")
                nickname = value;
            else if (name == "text")
                text = value;
            else if (name == "file")
                std::cerr << "file size: " << value.size() << std::endl;
        }
    }

    auto content_length = request.base()[http::field::content_length];
    //std::cerr << request_body << std::endl;
    if (!file.empty())
        std::cerr << "FILE" << file << std::endl;

    if (nickname.empty() || nickname.find('\n') != std::string::npos)
        return bad_request("Invalid nickname");

    try {
        static Redis redis;
        static Comments comments;
        auto spamlist = redis.spamlist();
        for (const auto &s : spamlist) {
            if (text.find(s) != std::string::npos)
                return server_error("spam detected");
        }
        comments.add(nickname, text);
        std::cerr << nickname << " posted" << std::endl;

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

message_generator request_handler::get_invite(std::string invite)
{
    return empty_body();
}

message_generator request_handler::post_invite(std::string invite)
{
    return empty_body();
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

message_generator request_handler::post_status(long long session)
{
    std::string status;

    auto request_body = request.body();
    auto url="http://post.data/?" + request_body;
    urls::url_view uv(url);
    auto pv = uv.params();
    for (auto p : pv) {
        if (p.key == "status")
            status = p.value;
    }

    if (status.empty() || status.find('\n') != std::string::npos || status.size() > 128)
        return bad_request("Invalid status");

    try {
        static Redis redis;
        std::string login{redis.session_login(session)};
        redis.status(status);

        std::string body = "you successfully changed status";
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

message_generator request_handler::response()
{
    std::string target = request.target();
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

    
    bool have_session = cookie.find("session_hash") != std::string::npos;
    long long session = -1;
    std::string session_hash;
    if (have_session) {
        // Validate session
        std::istringstream C(cookie);
        std::string c;
        while (C >> c) {
            if (c.back() == ';')
                c.pop_back();
            auto eq = c.find('=');
            if (eq != std::string::npos) {
                std::string k(c, 0, eq);
                std::string v(c, eq + 1, c.size() - eq);
                if (k == "session") {
                    std::istringstream V(v);
                    V >> session;
                } else if (k == "session_hash")
                    session_hash = v;
            }
        }

        static Redis redis;
        auto valid_sessionhash = redis.session_hash(session);
        if (session >= 0)
            have_session = have_session && (session_hash == valid_sessionhash);
        else
            have_session = false;
    }

    if (!have_session)
        session = -1;

    std::cerr << request.method() << " " << target << " " << forwarded << " session=" << session << std::endl;
    //std::cerr << "Cookie: " << cookie << std::endl;

    if (target == "/" && method == http::verb::get) {
        return get_root(session);
    } else if (target == "/" && method == http::verb::post) {
        if (have_session)
            return post_root(session);
        else
            return bad_request("you must accept cookies");
    }

    if (target == "/invite" && method == http::verb::post) {
        return empty_body();//new_invite();
    }

    auto invite_base = "/invite/"s;
    if (target.starts_with(invite_base)) {
        auto invite = target.substr(invite_base.size());
        return get_invite(invite);
    }

    if (target == "/season1.html" && method == http::verb::get) {
        return get_season("season1");
    } else if (target == "/season1.html" && method == http::verb::post) {
        return empty_body();
    }

    if (target == "/season2.html" && method == http::verb::get) {
        return get_season("season2");
    } else if (target == "/season2.html" && method == http::verb::post) {
        return empty_body();
    }

    if (target == "/season3.html" && method == http::verb::get) {
        return get_season("season3");
    } else if (target == "/season3.html" && method == http::verb::post) {
        return empty_body();
    }

    if (target == "/season4.html" && method == http::verb::get) {
        return get_season("season4");
    } else if (target == "/season4.html" && method == http::verb::post) {
        return empty_body();
    }

    if (target == "/season5.html" && method == http::verb::get) {
        return get_season("season5");
    } else if (target == "/season5.html" && method == http::verb::post) {
        return empty_body();
    }

    if (target == "/season6.html" && method == http::verb::get) {
        return get_season("season6");
    } else if (target == "/season6.html" && method == http::verb::post) {
        return empty_body();
    }

    if (target == "/season7.html" && method == http::verb::get) {
        return get_season("season7");
    } else if (target == "/season7.html" && method == http::verb::post) {
        return empty_body();
    }

    if (target == "/season8.html" && method == http::verb::get) {
        return get_season("season8");
    } else if (target == "/season8.html" && method == http::verb::post) {
        return empty_body();
    }

    if (target == "/season9.html" && method == http::verb::get) {
        return get_season("season9");
    } else if (target == "/season9.html" && method == http::verb::post) {
        return empty_body();
    }

    if (target == "/robots.txt")
        return wiki();

    if (target == "/login.html" && method == http::verb::get) {
        return login(session);
    } else if (target == "/login.html" && method == http::verb::post) {
        return post_login(session);
    }

    if (target == "/status" && method == http::verb::post) {
        return post_status(session);
    }

    return not_found(request.target());
}
