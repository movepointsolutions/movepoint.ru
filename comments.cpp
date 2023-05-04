#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include "comment.h"
#include "comments.h"
#include "redis.h"

const char *comments_key = "movepoint.ru:comments";

std::string Comments::content(const char *key)
{
    if (key == NULL)
        key = comments_key;

    //TODO: optimize&cleanup
	auto redis = get_redis();
    std::vector<std::string> cs;
	redis.lrange(key, 0, -1, std::back_inserter(cs));

    std::vector<Comment> comments;
    for (const auto &c : cs) {
        std::istringstream s(c);
        Comment cmt;
        s >> cmt;
        comments.push_back(cmt);
    }

    std::stringstream s;
    std::copy(std::begin(comments),
              std::end(comments),
              std::ostream_iterator<Comment>(s));
    return s.str();
}

void Comments::add(const std::string &nickname, const std::string &text)
{
	auto redis = get_redis();
	redis.rpush(comments_key, nickname + "\n" + text);
}
