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
};

template <const char *TagName>
struct tag : public tag_base
{
	std::string content() const {
		using namespace std::string_literals;
		return "<"s + TagName + " " + this->attrshtml() + ">"
		       + this->innerhtml()
		       + "</"s + TagName + ">";
	}
};

#endif // ENGINE_H
