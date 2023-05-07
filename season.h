#ifndef SEASON1_H
#define SEASON1_H

#include <string>

class Season
{
    std::string key;

public:
    Season(const std::string &_key);
    std::string content() const;
};

#endif // SEASON1_H
