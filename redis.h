#ifndef REDIS_H
#define REDIS_H

#include <string>

class Redis
{
public:
	void leave_comment(const std::string &nickname, const std::string &text);
	std::string comments();
};

#endif // REDIS_H
