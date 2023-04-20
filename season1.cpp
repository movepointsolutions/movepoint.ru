#include <iostream>
#include <stdexcept>
#include "season1.h"
#include "track.h"
#include "engine.h"
#include "comments.h"

using namespace std::string_literals;

Season::Season(const std::string &_key)
    : key(_key)
    , fhead("head.htm")
{
    thead << fhead.rdbuf();
}

std::string Season::content() const
{
    Redis redis;
    redis.hit();
    Comments comments;
    const std::string k = "movepoint.ru:" + key;
    auto archive = comments.content(k.c_str());
    auto doctype = "<!DOCTYPE html>"s;
    tags::html html;
    html.push_attr("lang", "ru");
    tags::head head;
    head.innerhtml(thead.str());
    tags::body body;
    tags::div container;
    container.push_attr("class", "container");
    tags::h2 h2;
    h2.innerhtml("Comments (" + key + ")");
    container.innerhtml(h2.content() + archive);
    body.innerhtml(container.content());
    html.innerhtml(head.content() + body.content());
    return doctype + html.content();
}
