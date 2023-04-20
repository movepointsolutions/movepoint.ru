#ifndef SEASON1_H
#define SEASON1_H

#include <fstream>
#include <sstream>
#include <string>
#include "redis.h"

class Season
{
    std::string key;
    std::ifstream fhead;
    std::ostringstream thead;

public:
    Season(const std::string &_key);
    std::string content() const;
};

#endif // SEASON1_H
