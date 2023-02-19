#include <iostream>
#include <stdexcept>
#include "season3.h"
#include "track.h"
#include "engine.h"

using namespace std::string_literals;

Season3::Season3()
    : fhead("head.htm")
    , findex("index.html")
    , farchive("season3.html")
    , ftail("tail.htm")
{
    thead << fhead.rdbuf();
    tindex << findex.rdbuf();
    tarchive << farchive.rdbuf();
    ttail << ftail.rdbuf();
}

std::string Season3::content() const
{
    Redis redis;
    redis.hit();
    auto archive = redis.archive("movepoint.ru:season3");
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
