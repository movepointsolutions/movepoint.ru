#ifndef RECORDS_H
#define RECORDS_H

#include <string>

struct Records
{
    std::string content(const char *key = NULL);
	void add(const std::string &meta, const std::string &url);
};

#endif // RECORDS_H
