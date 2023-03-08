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
    , s_commenttoo("comment_too.htm")
    , s_lina("lina.html")
    , s_tail("tail.htm")
    , s_script("script.js")
    , s_style("style.css")
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
    tags::style style;
    style.innerhtml(s_style.content());
    head.innerhtml(s_head.content() + style.content());
    tags::body body;
    tags::div container;
    container.push_attr("class", "container");
    tags::div container1;
    container1.push_attr("class", "container col-md-8");
    tags::h2 comments;
    comments.innerhtml("Комментарии"s);
    tags::p seasons;
    {
	    tags::a season1;
	    season1.push_attr("href", "/season1.html");
	    season1.innerhtml("Season 1");
	    tags::a season2;
	    season2.push_attr("href", "/season2.html");
	    season2.innerhtml("Season 2");
	    tags::a season3;
	    season3.push_attr("href", "/season3.html");
	    season3.innerhtml("Season 3");
	    seasons.innerhtml(season1.content() + season2.content() + season3.content());
    }
    seasons.push_attr("class", "hidden");
    container1.innerhtml(comments.content() + seasons.content() + redis.comments() + s_commenttoo.content());
    tags::div container2;
    container2.push_attr("class", "container col-md-4");
    container2.innerhtml(s_lina.content());
    container.innerhtml(container1.content() + container2.content());
    tags::script script;
    script.innerhtml(s_script.content());
    auto bodyhtml = s_index.content() + container.content() + script.content() + s_tail.content();
    body.innerhtml(bodyhtml);
    html.innerhtml(head.content() + body.content());
    return doctype + html.content();
}
