#ifndef SEASON3_H
#define SEASON3_H

#include <fstream>
#include <sstream>
#include <string>
#include "redis.h"

class Season3
{
    std::ifstream fhead;
    std::ifstream findex;
    std::ifstream farchive;
    std::ifstream fcomments;
    std::ifstream ftail;
    std::ostringstream thead;
    std::ostringstream tindex;
    std::ostringstream tarchive;
    std::ostringstream tcomments;
    std::ostringstream ttail;

public:
    Season3();
    std::string content() const;
};

#endif // SEASON3_H
