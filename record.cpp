#include <sstream>
#include "record.h"
#include "engine.h"

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

static std::string limit(std::string str, size_t size)
{
	if (str.size() > size)
		str.resize(size);
	std::string::iterator i = str.begin();
	while (true) {
		std::string::iterator j = i;
		for (int k = 0; k < 80; k++) {
			if (*j == '\n')
				k = 1;
			if (j != str.end())
				++j;
		}
		if (j == str.end())
			break;
		while (*j != ' ' && j != str.end())
			j++;
		if (j == str.end())
			break;
		*j = '\n';
		i = ++j;
	}
	return str;
}

std::istream &operator >>(std::istream &stream, Record &record)
{
    std::string meta, link;
    std::getline(stream, meta);
    std::getline(stream, link);
    record.a_link = record.f_link = link;
/*
    const std::string old = "pub/demo2023";
    size_t i = record.a_link.find(old);
    record.a_link.replace(i, old.size(), "Tribute");
*/
    meta = escape(meta);
    meta = limit(meta, 256);
    std::istringstream I(meta);
    I >> record.no;
    std::getline(I, record.name, '(');
    std::getline(I, record.group, ')');
    return stream;
}

std::ostream &operator <<(std::ostream &stream, const Record &record)
{
#include "record.view"
    return stream << record_view() << std::endl;
}
