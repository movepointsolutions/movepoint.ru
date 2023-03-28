#ifndef REDIS_H
#define REDIS_H

#include <string>

class Redis
{
public:
	void hit();
	long long hits();
	void leave_comment(const std::string &nickname, const std::string &text);
	std::string status();
	std::string comments();
	std::string archive(const char *id);
};

#endif // REDIS_H
