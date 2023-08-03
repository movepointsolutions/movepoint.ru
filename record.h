#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <iostream>

struct Record
{
    int no;
    std::string name;
    std::string group;
    std::string a_link;
    std::string f_link;
};

std::istream &operator >>(std::istream &stream, Record &record);
std::ostream &operator <<(std::ostream &stream, const Record &record);

#endif // COMMENT_H
