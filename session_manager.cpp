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
    std::string slt;
    std::ifstream S("session_salt");
    if (!(S >> slt))
        throw std::runtime_error("can't load salt");
    std::swap(salt, slt);
}

std::string session_manager::get_sessionhash(long long session)
{
    std::ostringstream S;
    S << salt << session << salt;

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
