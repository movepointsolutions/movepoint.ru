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
	long long new_session();
	std::string status();
};

#endif // REDIS_H
