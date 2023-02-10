#include "engine.h"

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