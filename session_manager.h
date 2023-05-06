#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <string>

class session_manager
{
    std::string salt;

public:
    session_manager();
    std::string get_sessionhash(long long session);
};

#endif // SESSION_MANAGER_H
