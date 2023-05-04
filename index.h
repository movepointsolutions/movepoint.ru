#ifndef INDEX_H
#define INDEX_H

#include <string>
#include "redis.h"
#include "snippet.h"

class Index
{
    snippet s_head;
    snippet s_index;
    snippet s_archive;
    snippet s_commenttoo;
    snippet s_tail;
    snippet s_script;
    snippet s_style;
    snippet s_header;
    snippet s_rutracker;

public:
    Index();
    std::string content() const;
};

#endif // INDEX_H
