#include <iostream>
#include <stdexcept>
#include "index.h"
#include "track.h"
#include "engine.h"

using namespace std::string_literals;

const char t_html[] = "html";
const char t_head[] = "head";
const char t_body[] = "body";

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
    tag<t_html> html;
    html.push_attr("lang=\"ru\"");
    tag<t_head> head;
    head.innerhtml(thead.str());
    tag<t_body> body;
    auto bodyhtml = tindex.str() + tcomments.str() + redis.comments() + tcommenttoo.str() + ttail.str();
    body.innerhtml(bodyhtml);
    html.innerhtml(head.content() + body.content());
    return doctype + html.content();
}
