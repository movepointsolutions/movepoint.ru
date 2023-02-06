#include <stdexcept>
#include "index.h"

Index::Index()
    : fhead("head.htm")
    , findex("index.html")
    , ftail("tail.htm")
{
    head << fhead.rdbuf();
    index << findex.rdbuf();
    tail << ftail.rdbuf();
}

Index::Redis::Redis()
    : ctx(redisConnect("127.0.0.1", 6379))
{
    if (ctx != NULL && ctx->err)
        throw std::runtime_error(ctx->errstr);
}

Index::Redis::~Redis()
{
    redisFree(ctx);
}

std::string Index::Redis::comments() const
{
    std::ostringstream ret;
    redisReply *reply;
    reply = static_cast<redisReply *>(redisCommand(ctx, "LRANGE movepoint.ru:comments 0 -1"));
    for (int i = 0; i < reply->elements; i++) {
        char *nick = reply->element[i]->str;
        char *comment = nick;
        while (*comment && *comment != '\n')
            comment++;
        *(comment++) = '\0';
        ret << "<div class=\"comment\">" << std::endl;
        ret << " <strong>" << nick << "</strong>" << std::endl;
        ret << " <br><i>" << comment << "</i>" << std::endl;
        ret << "</div>" << std::endl;
    }
    freeReplyObject(reply);
    return ret.str();
}

std::string Index::content() const
{
    return head.str() + index.str() + redis.comments() + tail.str();
}
