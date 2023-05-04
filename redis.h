#ifndef REDIS_H
#define REDIS_H

#include <functional>
#include <string>
#include <sw/redis++/redis++.h>
#include "comment.h"

sw::redis::Redis get_redis();

class Redis
{
public:
	void hit();
	long long hits();
	long long new_session();
	std::string status();
    std::vector<std::string> spamlist();
};

#endif // REDIS_H
