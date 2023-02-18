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
	std::string content() const {
		using namespace std::string_literals;
		return "<"s + TagName + " " + this->attrshtml() + ">"
		       + this->innerhtml()
		       + "</"s + TagName + ">";
	}
};

namespace tags
{
	extern const char t_html[];
	extern const char t_head[];
	extern const char t_body[];
	extern const char t_div[];

	typedef tag<t_html> html;
	typedef tag<t_head> head;
	typedef tag<t_body> body;
	typedef tag<t_div> div;
}

#endif // ENGINE_H
