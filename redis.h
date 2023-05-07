#ifndef REDIS_H
#define REDIS_H

#include <functional>
#include <string>
#include <utility>
#include <sw/redis++/redis++.h>
#include "comment.h"

sw::redis::Redis get_redis();

class Redis
{
public:
	void hit();
	long long hits();
	std::pair<long long, std::string> new_session();
    void login_session(long long, const std::string &);
    std::string session_login(long long);
    std::string display_name(const std::string &login);
    void session_hash(long long session, std::string sessionhash);
    std::string session_hash(long long);
    std::string password_hash(const std::string &);
	std::string status();
    std::vector<std::string> spamlist();
};

#endif // REDIS_H
