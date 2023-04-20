#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <sw/redis++/redis++.h>
#include "redis.h"

const std::string url = "tcp://127.0.0.1:6379";

static auto get_redis()
{
    auto ret = sw::redis::Redis(url);
    std::ifstream pwd("pwd");
    std::string pass;
    if (pwd >> pass) {
	    std::cerr << "AUTH..." << std::endl;
	    ret.auth(pass);
	    std::cerr << "AUTH OK" << std::endl;
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
	std::cerr << "HIT..." << std::endl;
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
