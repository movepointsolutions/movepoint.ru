#include <iostream>
#include <stdexcept>
#include "season.h"
#include "engine.h"
#include "comments.h"
#include "redis.h"
#include "snippet.h"

using namespace std::string_literals;

Season::Season(const std::string &_key)
    : key(_key)
{
}

std::string Season::content() const
{
    Redis redis;
    redis.hit();
    tags::h2 h2;
    h2.innerhtml("Comments (" + key + ")");
    Comments comments;
    const std::string k = "movepoint.ru:" + key;
    auto archive = comments.content(k.c_str());
#include "page.view"
    return page_view(false, h2.content() + archive);
}
