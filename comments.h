#ifndef COMMENTS_H
#define COMMENTS_H

#include <string>
#include <boost/asio/spawn.hpp>

class Comments
{
    typedef boost::asio::yield_context yield_context;

public:
    std::string content(const char *key = NULL);
	void add(const std::string &nickname, const std::string &text,
             const std::string &captcha, yield_context yield);
};

#endif // COMMENTS_H
