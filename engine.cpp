#include "engine.h"

namespace tags {
	const char t_html[] = "html";
	const char t_head[] = "head";
	const char t_body[] = "body";
	const char t_div[] = "div";
	const char t_h1[] = "h1";
	const char t_h2[] = "h2";
	const char t_h3[] = "h3";
	const char t_script[] = "script";
	const char t_a[] = "a";
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
	for (const auto a : attrs) {
		ret += " ";
		ret += a;
	}
	return ret;
}
