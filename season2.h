#ifndef SEASON2_H
#define SEASON2_H

#include <fstream>
#include <sstream>
#include <string>
#include "redis.h"

class Season2
{
    std::ifstream fhead;
    std::ifstream findex;
    std::ifstream farchive;
    std::ifstream ftail;
    std::ostringstream thead;
    std::ostringstream tindex;
    std::ostringstream tarchive;
    std::ostringstream ttail;

public:
    Season2();
    std::string content() const;
};

#endif // SEASON2_H
