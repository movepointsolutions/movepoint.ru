#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <iostream>

struct Comment
{
    std::string nickname;
    std::string text;
};

std::istream &operator >>(std::istream &stream, Comment &comment);
std::ostream &operator <<(std::ostream &stream, const Comment &comment);

#endif // COMMENT_H
