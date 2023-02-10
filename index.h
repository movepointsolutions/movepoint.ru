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
    std::ifstream farchive;
    std::ifstream fcomments;
    std::ifstream fcommenttoo;
    std::ifstream ftail;
    std::ostringstream thead;
    std::ostringstream tindex;
    std::ostringstream tarchive;
    std::ostringstream tcomments;
    std::ostringstream tcommenttoo;
    std::ostringstream ttail;

public:
    Index();
    std::string content() const;
};

#endif // INDEX_H
