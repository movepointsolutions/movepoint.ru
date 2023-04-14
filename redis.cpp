#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <sw/redis++/redis++.h>
#include "redis.h"

const std::string url = "tcp://127.0.0.1:6379";
const std::string key = "movepoint.ru:comments";

static auto get_redis()
{
    auto ret = sw::redis::Redis(url);
    std::ifstream pwd("pwd");
    std::string pass;
    pwd >> pass;
    ret.auth(pass);
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
	redis.incr("movepoint.ru:hits");
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

void Redis::leave_comment(const std::string &nickname, const std::string &text)
{
	auto redis = get_redis();
	//std::cerr << "Nickname: " << nickname << std::endl;
	//std::cerr << "Text: " << text << std::endl;
	redis.rpush(key, nickname + "\n" + text);
}

static std::string comments(const char *key)
{
	//std::cerr << "Fetching comments" << std::endl;
	auto redis = get_redis();
	std::ostringstream ret;
	std::vector<std::string> elements;
	//std::cerr << "Comments: " << elements.size() << std::endl;
	redis.lrange(key, 0, -1, std::back_inserter(elements));
	//std::cerr << "Comments: " << elements.size() << std::endl;
	for (auto element : elements) {
		std::ostringstream comment;
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
		comment << indent << "<article class=\"comment\"><pre>" << std::endl;
		comment << indent << " <h4>" << nickname << "</h4>" << std::endl;
		comment << indent << " <i>" << text << "</i>" << std::endl;
		comment << indent << "</pre></article>" << std::endl;
		ret << comment.str();
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
