#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <sw/redis++/redis++.h>
#include "redis.h"
#include "session_manager.h"

const std::string url = "tcp://127.0.0.1:6379";

sw::redis::Redis get_redis()
{
    auto ret = sw::redis::Redis(url);
    std::ifstream pwd("pwd");
    std::string pass;
    if (pwd >> pass) {
	    ret.auth(pass);
	    //std::cerr << "AUTH_OK" << std::endl;
    }
    return ret;
}

static std::string escape(const std::string &str)
{
	std::ostringstream ret;
	for (const char c : str) {
		if (c == '<')
			ret << "&lt;";
		else if (c == '>')
			ret << "&gt;";
		else
			ret << c;
	}
	return ret.str();
}

static std::string limit(std::string str, size_t size)
{
	if (str.size() > size)
		str.resize(size);
	std::string::iterator i = str.begin();
	while (true) {
		std::string::iterator j = i;
		for (int k = 0; k < 107; k++) {
			if (*j == '\n')
				k = 1;
			if (j != str.end())
				++j;
		}
		if (j == str.end())
			break;
		while (*j != ' ' && j != str.end())
			j++;
		if (j == str.end())
			break;
		*j = '\n';
		i = ++j;
	}
	return str;
}

void Redis::hit()
{
	auto redis = get_redis();
	//std::cerr << "HIT..." << std::endl;
    try {
	    redis.incr("movepoint.ru:hits");
    } catch (...) {
    	std::cerr << "Can't record hit" << std::endl;
        //throw;
    }
}

long long Redis::hits()
{
	auto redis = get_redis();
	return redis.command<long long>("get", "movepoint.ru:hits");
}

std::pair<long long, std::string> Redis::new_session()
{
	auto redis = get_redis();
	auto session = redis.command<long long>("incr", "movepoint.ru:session");
    static session_manager sm;
    auto shash = sm.get_sessionhash(session);
    session_hash(session, shash);
    return std::make_pair(session, shash);
}

std::string Redis::new_invite(const std::string &login)
{
	auto redis = get_redis();
    static session_manager sm;
    auto ihash = sm.get_invitehash(login);
    invite_hash(login, ihash);
    return ihash;
}

void Redis::login_session(long long session, const std::string &login)
{
    std::ostringstream K;
    K << "movepoint.ru:session:" << session << ":login";
    std::string key{K.str()};
	auto redis = get_redis();
	redis.set(key, login);
}

std::string Redis::session_login(long long session)
{
    std::ostringstream K;
    K << "movepoint.ru:session:" << session << ":login";
    std::string key{K.str()};
	auto redis = get_redis();
	auto v = redis.get(key);
    if (v.has_value())
        return v.value();
    else
        return std::string();
}

std::string Redis::display_name(const std::string &login)
{
    std::ostringstream K;
    K << "movepoint.ru:acc:" << login << ":dn";
    std::string key{K.str()};
	auto redis = get_redis();
	auto v = redis.get(key);
    if (v.has_value())
        return v.value();
    else
        return std::string();
}

void Redis::invite_hash(const std::string &login, const std::string &invitehash)
{
    std::ostringstream K;
    K << "movepoint.ru:invite:" << login << ":hash";
    std::string key{K.str()};
	auto redis = get_redis();
	redis.set(key, invitehash);
}

void Redis::session_hash(long long session, const std::string &sessionhash)
{
    std::ostringstream K;
    K << "movepoint.ru:session:" << session << ":hash";
    std::string key{K.str()};
	auto redis = get_redis();
	redis.set(key, sessionhash);
}

std::string Redis::session_hash(long long session)
{
    //std::string key{std::format("movepoint.ru:session:{}:hash", session);
    std::ostringstream K;
    K << "movepoint.ru:session:" << session << ":hash";
    //std::string key{std::format("movepoint.ru:session:{}:hash", session);
    std::string key{K.str()};
	auto redis = get_redis();
	auto v = redis.get(key);
    if (v.has_value())
        return v.value();
    else
        return std::string();
}

std::string Redis::password_hash(const std::string &login)
{
    std::ostringstream K;
    K << "movepoint.ru:acc:" << login << ":ph";
    std::string key{K.str()};
	auto redis = get_redis();
	auto v = redis.get(key);
    if (v.has_value())
        return v.value();
    else
        return std::string();
}

std::string Redis::invite_hash(const std::string &login)
{
    std::ostringstream K;
    K << "movepoint.ru:invite:" << login << ":ih";
    std::string key{K.str()};
	auto redis = get_redis();
	auto v = redis.get(key);
    if (v.has_value())
        return v.value();
    else
        return std::string();
}

std::string Redis::status()
{
	auto redis = get_redis();
	std::vector<std::string> statuses;
	redis.lrange("movepoint.ru:status", -1, -1, std::back_inserter(statuses));
	std::ostringstream ret;
	for (const auto &s : statuses)
		ret << escape(s);
	return ret.str();
}

void Redis::status(const std::string &s)
{
	auto redis = get_redis();
	std::vector<std::string> statuses;
	redis.rpush("movepoint.ru:status", s);
}

std::vector<std::string> Redis::spamlist()
{
	auto redis = get_redis();
    const char *key = "spamlist";
    std::vector<std::string> ret;
	redis.lrange(key, 0, -1, std::back_inserter(ret));
    return ret;
}
