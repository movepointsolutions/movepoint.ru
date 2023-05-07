#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

class request_handler
{
    typedef boost::beast::http::string_body body_type;
    typedef boost::beast::http::request<body_type> request_type;
    using message_generator = boost::beast::http::message_generator;

protected:
    message_generator bad_request(boost::beast::string_view why);
    message_generator not_found(boost::beast::string_view target);
    message_generator server_error(boost::beast::string_view what);
    message_generator empty_body(boost::beast::string_view target);
    message_generator wiki();
    message_generator login(long long session);
    message_generator get_root(long long session);
    message_generator post_root(long long session);
    message_generator get_season(const std::string &);

public:
    std::string doc_root;
    request_type request;

    request_handler(const std::string &, request_type &&);
    boost::beast::http::message_generator response();
};
