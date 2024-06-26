#include <iostream>
#include <sstream>
#include <stdexcept>
#include "index.h"
#include "track.h"
#include "engine.h"
#include "comments.h"
#include "records.h"
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
    static snippet s_album("album.html");
    static snippet s_torrent("torrent.html");
    static snippet s_don("don.html");
    tags::div container;
    container.push_attr("class", "container");
    tags::div container1;
    container1.push_attr("class", "container col-md-8");
    tags::h2 comments_header;
    comments_header.innerhtml("Комментарии"s);
    tags::p seasons;
    std::ostringstream S;
    for (int s = 1; s <= 9; s++) {
        std::ostringstream link, label;
        link << "/season/" << s;
        label << "Season" << s;

	    tags::a season;
	    season.push_attr("href", link.str());
	    season.innerhtml(label.str());
        S << season.content();
    }
    tags::a tg;
    tg.push_attr("href", "https://t.me/+2islB6n2lxJhMjhi");
    tg.innerhtml("TG");
    S << tg.content();
    seasons.innerhtml(S.str());
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
    Records records;
    tags::div demo2023;
    demo2023.push_attr("id", "demo2023");
    demo2023.innerhtml(s_album.content()
                     + records.content()
                     + s_don.content());
    auto bodyhtml = header_view(dn) + status.content()
                    + demo2023.content()
                    + s_torrent.content()
                    //+ video_view(login) + s_rutracker.content()
	                + container.content() + script.content();
#include "page.view"
    return page_view(true, bodyhtml);
}
