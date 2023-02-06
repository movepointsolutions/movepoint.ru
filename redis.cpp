#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <sw/redis++/redis++.h>
#include "redis.h"

const std::string key = "movepoint.ru:comments";

void Redis::leave_comment(const std::string &nickname, const std::string &text)
{
	auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");
	std::cerr << "Nickname: " << nickname << std::endl;
	std::cerr << "Text: " << text << std::endl;
	redis.rpush(key, nickname + "\n" + text);
}

std::string Redis::comments()
{
	std::cerr << "Fetching comments" << std::endl;
	auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");
	std::ostringstream ret;
	std::vector<std::string> elements;
	std::cerr << "Comments: " << elements.size() << std::endl;
	redis.lrange(key, 0, -1, std::back_inserter(elements));
	std::cerr << "Comments: " << elements.size() << std::endl;
	for (auto element : elements) {
		const char *n = element.c_str();
		const char *c = n;
		while (*c && *c != '\n')
			c++;
		std::string nickname(n, c);
		std::string text(++c);
		ret << "<article class=\"comment\">" << std::endl;
		ret << " <strong>" << nickname << "</strong>" << std::endl;
		ret << " <br><i>" << text << "</i>" << std::endl;
		ret << "</article>" << std::endl;
	}
	return ret.str();
}

