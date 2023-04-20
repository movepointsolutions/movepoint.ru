#ifndef REDIS_H
#define REDIS_H

#include <functional>
#include <string>
#include "comment.h"

class Redis
{
public:
	void hit();
	long long hits();
	std::string status();
};

#endif // REDIS_H
