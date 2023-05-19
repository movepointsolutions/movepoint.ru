#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <string>

class session_manager
{
    std::string session_salt;
    std::string password_salt;
    std::string invite_salt;

public:
    session_manager();
    std::string get_sessionhash(long long session);
    std::string get_passwordhash(const std::string &password);
    std::string get_invitehash(const std::string &invite);
};

#endif // SESSION_MANAGER_H
