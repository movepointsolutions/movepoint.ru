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
    std::ostringstream head;
    std::ostringstream index;
    std::ostringstream archive;
    std::ostringstream comments;
    std::ostringstream tail;

public:
    Season1();
    std::string content() const;
};

#endif // SEASON1_H
