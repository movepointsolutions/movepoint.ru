#include <iostream>
#include <stdexcept>
#include "index.h"
#include "track.h"
#include "engine.h"
#include "comments.h"
#include "redis.h"
#include "snippet.h"

using namespace std::string_literals;

Index::Index(const std::string &ul)
    : user_login(ul)
{
}

static std::string escape(const std::string &str)
{
	std::ostringstream ret;
	for (const char c : str) {
		if (c == '<')
			ret << "&lt;";
		else if (c == '>')
			ret << "&gt;";
		else
			ret << c;
	}
	return ret.str();
}

std::string Index::content(long long session) const
{
    Redis redis;
    redis.hit();
    static snippet s_index("index.html");
    static snippet s_desc("desc.htm");
    static snippet s_script("script.js");
    static snippet s_rutracker("rutracker.htm");
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
	    tags::a season5;
	    season5.push_attr("href", "/season5.html");
	    season5.innerhtml("Season 5");
	    seasons.innerhtml(season1.content()
                         + season2.content()
                         + season3.content()
                         + season4.content()
                         + season5.content()
       );
    }
    //seasons.push_attr("class", "hidden");
    Comments comments;
#include "comment.view"
#include "status.view"
#include "invite.view"
    container1.innerhtml(comments_header.content() + seasons.content() +
                         status_view(session) +
                         invite_view(session) +
                         comments.content() + comment_view(session));
    tags::div container2;
    container2.push_attr("class", "container col-md-4");
#include "lina.view"
    container2.innerhtml(lina_view());
    container.innerhtml(container1.content() + container2.content());
    tags::script script;
    script.innerhtml(s_script.content());
#include "header.view"
    auto login = redis.session_login(session);
    auto dn = redis.display_name(login);
    tags::h2 status;
    status.innerhtml(redis.status() + " edition");
#include "video.view"
    auto bodyhtml = header_view(dn) + status.content()
                    + s_desc.content() + video_view(login) + s_rutracker.content()
	                + container.content() + script.content();
#include "page.view"
    return page_view(true, bodyhtml);
}
