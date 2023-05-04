#include <iostream>
#include <stdexcept>
#include "index.h"
#include "track.h"
#include "engine.h"
#include "comments.h"

using namespace std::string_literals;

Index::Index()
    : s_head("head.htm")
    , s_index("index.html")
    , s_archive("archive.htm")
    , s_commenttoo("comment_too.htm")
    , s_tail("tail.htm")
    , s_script("script.js")
    , s_style("style.css")
    , s_header("header.htm")
    , s_rutracker("rutracker.htm")
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
    tags::h2 comments_header;
    comments_header.innerhtml("Комментарии"s);
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
	    tags::a season4;
	    season4.push_attr("href", "/season4.html");
	    season4.innerhtml("Season 4");
	    seasons.innerhtml(season1.content()
                         + season2.content()
                         + season3.content()
                         + season4.content());
    }
    //seasons.push_attr("class", "hidden");
    Comments comments;
    container1.innerhtml(comments_header.content() + seasons.content() + comments.content() + s_commenttoo.content());
    tags::div container2;
    container2.push_attr("class", "container col-md-4");
#include "lina.view"
    container2.innerhtml(lina_view());
    container.innerhtml(container1.content() + container2.content());
    tags::script script;
    script.innerhtml(s_script.content());
    tags::header header;
    tags::h2 status;
    status.innerhtml(redis.status() + " edition");
    header.innerhtml(s_header.content() + status.content());
    auto bodyhtml = header.content() + s_index.content() + s_rutracker.content()
	            + container.content() + script.content(); //+ s_tail.content();
    tags::div outer_container;
    outer_container.push_attr("class", "container");
    outer_container.innerhtml(bodyhtml);
    body.innerhtml(outer_container.content());
    html.innerhtml(head.content() + body.content());
    return doctype + html.content();
}
