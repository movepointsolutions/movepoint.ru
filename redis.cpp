#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <sw/redis++/redis++.h>
#include "redis.h"

const std::string key = "movepoint.ru:comments";

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
	return str;
}

void Redis::hit()
{
	auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");
	redis.incr("movepoint.ru:hits");
}

long long Redis::hits()
{
	auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");
	return redis.command<long long>("get", "movepoint.ru:hits");
}

void Redis::leave_comment(const std::string &nickname, const std::string &text)
{
	auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");
	//std::cerr << "Nickname: " << nickname << std::endl;
	//std::cerr << "Text: " << text << std::endl;
	redis.rpush(key, nickname + "\n" + text);
}

static std::string comments(const char *key)
{
	//std::cerr << "Fetching comments" << std::endl;
	auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");
	std::ostringstream ret;
	std::vector<std::string> elements;
	//std::cerr << "Comments: " << elements.size() << std::endl;
	redis.lrange(key, 0, -1, std::back_inserter(elements));
	//std::cerr << "Comments: " << elements.size() << std::endl;
	for (auto element : elements) {
		const char *n = element.c_str();
		const char *c = n;
		int count = 0;
		while (*c && *c != '\n')
			c++;
		std::string nickname(n, c);
		std::string text(++c);
		std::string indent = "  ";
		nickname = escape(nickname);
		text = escape(text);
		nickname = limit(nickname, 64);
		text = limit(text, 16384);
		ret << indent << "<article class=\"comment\">" << std::endl;
		ret << indent << " <h4>" << nickname << "</h4>" << std::endl;
		ret << indent << " <i>" << text << "</i>" << std::endl;
		ret << indent << "</article>" << std::endl;
	}
	return ret.str();
}

std::string Redis::comments()
{
	return ::comments(key.c_str());
}

std::string Redis::archive(const char *key)
{
	return ::comments(key);
}
