#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>

class tag_base
{
	std::vector<std::string> attrs;
	std::string innerhtml_;
public:
	std::string innerhtml() const;
	void innerhtml(const std::string &);
	std::string attrshtml() const;
	void push_attr(const std::string &);
	void push_attr(const std::string &, const std::string &);
};

template <const char *TagName>
struct tag : public tag_base
{
	std::string openhtml() const {
		using namespace std::string_literals;
		return "<"s + TagName + this->attrshtml() + ">";
	}
	std::string closehtml() const {
		using namespace std::string_literals;
		return "</"s + TagName + ">";
	}
	std::string content() const {
		return this->openhtml() + this->innerhtml() + this->closehtml();
	}
};

#define TAG(_tag) extern const char t_##_tag[]; typedef tag<t_##_tag> _tag;
namespace tags
{
#include "tags.h"
}
#undef TAG

#endif // ENGINE_H
