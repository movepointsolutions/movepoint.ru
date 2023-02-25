#include "engine.h"

#define TAG(tag) const char t_##tag[] = #tag
namespace tags {
#include "tags.h"
}
#undef TAG

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
