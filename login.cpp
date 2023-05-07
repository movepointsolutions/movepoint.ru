#include <iostream>
#include <stdexcept>
#include "login.h"
#include "track.h"
#include "redis.h"
#include "engine.h"
#include "snippet.h"

using namespace std::string_literals;

Login::Login()
{
}

std::string Login::content() const
{
    Redis redis;
    redis.hit();
    tags::h2 h2;
    h2.innerhtml("Login");
    static snippet s_loginform("login.htm");
#include "page.view"
    return page_view(true, h2.content() + s_loginform.content());
}
