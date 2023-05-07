#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>
extern "C" {
#include "sha1/sha1.h"
}
#include "session_manager.h"

session_manager::session_manager()
{
    auto load_salt = [](auto filename, std::string &salt) {
        std::string slt;
        std::ifstream S(filename);
        if (!(S >> slt))
            throw std::runtime_error("can't load salt");
        std::swap(salt, slt);
    };
    load_salt("session_salt", session_salt);
    load_salt("login_salt", password_salt);
}

std::string session_manager::get_sessionhash(long long session)
{
    std::ostringstream S;
    S << session_salt << session << session_salt;

    SHA_CTX ctx;
    SHA1_Init(&ctx);
    std::string data{S.str()};
    SHA1_Update(&ctx, data.c_str(), data.size());
    unsigned char rawhash[20];
    SHA1_Final(rawhash, &ctx);
    
    std::ostringstream S1;
    S1 << std::hex;
    for (unsigned char c : rawhash)
        S1 << (int)c;
    return S1.str();
}

std::string session_manager::get_passwordhash(const std::string &password)
{
    std::ostringstream S;
    S << password_salt << password << password_salt << password_salt;

    SHA_CTX ctx;
    SHA1_Init(&ctx);
    std::string data{S.str()};
    SHA1_Update(&ctx, data.c_str(), data.size());
    unsigned char rawhash[20];
    SHA1_Final(rawhash, &ctx);
    
    std::ostringstream S1;
    S1 << std::hex;
    for (unsigned char c : rawhash)
        S1 << (int)c;
    return S1.str();
}
