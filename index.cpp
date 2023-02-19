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
    auto doctype = "<!DOCTYPE html>"s;
    tags::html html;
    html.push_attr("lang", "ru");
    tags::head head;
    head.innerhtml(thead.str());
    tags::body body;
    tags::div container;
    container.push_attr("class", "container");
    container.innerhtml(tcomments.str() + redis.comments() + tcommenttoo.str());
    auto bodyhtml = tindex.str() + container.content() + ttail.str();
    body.innerhtml(bodyhtml);
    html.innerhtml(head.content() + body.content());
    return doctype + html.content();
}
