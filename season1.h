#ifndef SEASON1_H
#define SEASON1_H

#include <fstream>
#include <sstream>
#include <string>
#include "redis.h"

class Season1
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
    Season1();
    std::string content() const;
};

#endif // SEASON1_H
