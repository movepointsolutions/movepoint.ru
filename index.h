#ifndef INDEX_H
#define INDEX_H

#include <string>

class Index
{
    std::string user_login;
public:
    Index(const std::string &ul);
    std::string content(long long) const;
};

#endif // INDEX_H
