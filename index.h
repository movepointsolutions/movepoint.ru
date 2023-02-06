#ifndef INDEX_H
#define INDEX_H

#include <fstream>
#include <sstream>
#include <string>
#include "redis.h"

class Index
{
    std::ifstream fhead;
    std::ifstream findex;
    std::ifstream ftail;
    std::ostringstream head;
    std::ostringstream index;
    std::ostringstream tail;

public:
    Index();
    std::string content() const;
};

#endif // INDEX_H
