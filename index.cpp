#include <iostream>
#include <stdexcept>
#include "index.h"
#include "track.h"
#include "engine.h"

using namespace std::string_literals;

Index::Index()
    : fhead("head.htm")
    , findex("index.html")
    , farchive("archive.htm")
    , fcomments("comments.htm")
    , fcommenttoo("comment_too.htm")
    , ftail("tail.htm")
{
    thead << fhead.rdbuf();
    tindex << findex.rdbuf();
    tarchive << farchive.rdbuf();
    tcomments << fcomments.rdbuf();
    tcommenttoo << fcommenttoo.rdbuf();
    ttail << ftail.rdbuf();
}

std::string Index::content() const
{
    Redis redis;
    redis.hit();
    std::string a = redis.archive("movepoint.ru:archive0");
    auto doctype = "<!DOCTYPE html>"s;
    html::html htm;
    htm.push_attr("lang=\"ru\"");
    html::head head;
    head.innerhtml(thead.str());
    html::body body;
    auto bodyhtml = tindex.str() + tcomments.str() + redis.comments() + tcommenttoo.str() + ttail.str();
    body.innerhtml(bodyhtml);
    htm.innerhtml(head.content() + body.content());
    return doctype + htm.content();
}
