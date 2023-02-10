#include <iostream>
#include <stdexcept>
#include "season1.h"
#include "track.h"

Season1::Season1()
    : fhead("head.htm")
    , findex("index.html")
    , farchive("archive.htm")
    , fcomments("comments.htm")
    , ftail("tail.htm")
{
    head << fhead.rdbuf();
    index << findex.rdbuf();
    archive << farchive.rdbuf();
    comments << fcomments.rdbuf();
    tail << ftail.rdbuf();
}

std::string Season1::content() const
{
    Redis redis;
    redis.hit();
    std::string a = redis.archive("movepoint.ru:archive0");
    std::string ret = head.str() + index.str() + archive.str() + a + comments.str() + redis.comments() + tail.str();
    return ret;
}
