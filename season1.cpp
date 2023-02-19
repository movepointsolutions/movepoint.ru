#include <iostream>
#include <stdexcept>
#include "season1.h"
#include "track.h"
#include "engine.h"

using namespace std::string_literals;

Season1::Season1()
    : fhead("head.htm")
    , findex("index.html")
    , farchive("season1.html")
    , ftail("tail.htm")
{
    thead << fhead.rdbuf();
    tindex << findex.rdbuf();
    tarchive << farchive.rdbuf();
    ttail << ftail.rdbuf();
}

std::string Season1::content() const
{
    Redis redis;
    redis.hit();
    auto archive = redis.archive("movepoint.ru:season1");
    auto doctype = "<!DOCTYPE html>"s;
    tags::html html;
    html.push_attr("lang", "ru");
    tags::head head;
    head.innerhtml(thead.str());
    tags::body body;
    auto bodyhtml = tindex.str() + tarchive.str() + archive + ttail.str();
    body.innerhtml(bodyhtml);
    html.innerhtml(head.content() + body.content());
    return doctype + html.content();
}
