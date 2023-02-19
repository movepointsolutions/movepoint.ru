#include <iostream>
#include <stdexcept>
#include "index.h"
#include "track.h"
#include "engine.h"

using namespace std::string_literals;

Index::Index()
    : s_head("head.htm")
    , s_index("index.html")
    , s_archive("archive.htm")
    , s_comments("comments.htm")
    , s_commenttoo("comment_too.htm")
    , s_lina("lina.html")
    , s_tail("tail.htm")
{
}

std::string Index::content() const
{
    Redis redis;
    redis.hit();
    auto doctype = "<!DOCTYPE html>"s;
    tags::html html;
    html.push_attr("lang", "ru");
    tags::head head;
    head.innerhtml(s_head.content());
    tags::body body;
    tags::div container;
    container.push_attr("class", "container");
    tags::div container1;
    container1.push_attr("class", "container col-md-8");
    container.innerhtml(container1.openhtml() + s_comments.content() + redis.comments() + s_commenttoo.content());
    tags::div container2;
    container2.push_attr("class", "container col-md-4");
    container2.innerhtml(s_lina.content());
    auto bodyhtml = s_index.content() + container.content() + container2.content() + container1.closehtml() + s_tail.content();
    body.innerhtml(bodyhtml);
    html.innerhtml(head.content() + body.content());
    return doctype + html.content();
}
