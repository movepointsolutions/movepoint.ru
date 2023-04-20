#ifndef COMMENTS_H
#define COMMENTS_H

#include <string>

struct Comments
{
    std::string content(const char *key = NULL);
	void add(const std::string &nickname, const std::string &text);
};

#endif // COMMENTS_H
