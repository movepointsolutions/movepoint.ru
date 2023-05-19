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
	std::string new_invite(const std::string &);
    void login_session(long long, const std::string &);
    std::string session_login(long long);
    std::string display_name(const std::string &login);
    void invite_hash(const std::string &login, const std::string &invitehash);
    void session_hash(long long session, const std::string &sessionhash);
    std::string session_hash(long long);
    std::string password_hash(const std::string &);
    std::string invite_hash(const std::string &);
	std::string status();
	void status(const std::string &);
    std::vector<std::string> spamlist();
};

#endif // REDIS_H
