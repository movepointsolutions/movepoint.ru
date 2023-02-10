#include <iostream>
#include <stdexcept>
#include "season1.h"
#include "track.h"
#include "engine.h"

using namespace std::string_literals;

const char t_html[] = "html";
const char t_head[] = "head";
const char t_body[] = "body";

Season1::Season1()
    : fhead("head.htm")
    , findex("index.html")
    , farchive("archive.htm")
    , fcomments("comments.htm")
    , ftail("tail.htm")
{
    thead << fhead.rdbuf();
    tindex << findex.rdbuf();
    tarchive << farchive.rdbuf();
    tcomments << fcomments.rdbuf();
    ttail << ftail.rdbuf();
}

std::string Season1::content() const
{
    Redis redis;
    redis.hit();
    auto archive = redis.archive("movepoint.ru:archive0");
    auto doctype = "<!DOCTYPE html>"s;
    tag<t_html> html;
    html.push_attr("lang=\"ru\"");
    tag<t_head> head;
    head.innerhtml(thead.str());
    tag<t_body> body;
    auto bodyhtml = tindex.str() + tarchive.str() + archive + ttail.str();
    body.innerhtml(bodyhtml);
    html.innerhtml(head.content() + body.content());
    return doctype + html.content();
    //std::string ret = head.str() + index.str() + archive + tail.str();
    //return ret;
}
