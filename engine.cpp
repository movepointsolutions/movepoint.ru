#include "engine.h"

namespace tags {
	const char t_html[] = "html";
	const char t_head[] = "head";
	const char t_body[] = "body";
}

std::string tag_base::innerhtml() const
{
	return innerhtml_;
}

void tag_base::innerhtml(const std::string &i)
{
	innerhtml_ = i;
}

void tag_base::push_attr(const std::string &a)
{
	attrs.push_back(a);
}

void tag_base::push_attr(const std::string &an, const std::string &av)
{
	push_attr(an + "=\"" + av + "\"");
}

std::string tag_base::attrshtml() const
{
	std::string ret;
	bool first = true;
	for (const auto a : attrs) {
		if (!first)
			ret += " ";
		ret += a;
		first = false;
	}
	return ret;
}
