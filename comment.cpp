#include <sstream>
#include "comment.h"
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
		for (int k = 0; k < 107; k++) {
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

std::istream &operator >>(std::istream &stream, Comment &comment)
{
    std::getline(stream, comment.nickname);
    std::getline(stream, comment.text, '\0');
    comment.nickname = escape(comment.nickname);
    comment.text = escape(comment.text);
    comment.nickname = limit(comment.nickname, 64);
    comment.text = limit(comment.text, 16384);
    return stream;
}

std::ostream &operator <<(std::ostream &stream, const Comment &comment)
{
    tags::article article;
    article.push_attr("class", "comment");
    tags::h4 h4;
    h4.innerhtml(comment.nickname);
    tags::pre pre;
    tags::i i;
    i.innerhtml(comment.text);
    pre.innerhtml(i.content());
    article.innerhtml(h4.content() + pre.content());
    return stream << article.content() << std::endl;
}
