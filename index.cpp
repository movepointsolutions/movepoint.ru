#include <iostream>
#include <stdexcept>
#include "index.h"

Index::Index()
    : fhead("head.htm")
    , findex("index.html")
    , ftail("tail.htm")
{
    head << fhead.rdbuf();
    index << findex.rdbuf();
    tail << ftail.rdbuf();
}

std::string Index::content() const
{
    Redis redis;
    std::string h(head.str());
    std::cerr << "First byte: " << (int)(unsigned char)h[0] << std::endl;
    std::string ret = h + index.str() + redis.comments() + tail.str();
    std::cerr << "Index length: " << ret.size() << std::endl;
    return ret;
}
