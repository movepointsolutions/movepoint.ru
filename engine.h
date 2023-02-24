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

namespace tags
{
	extern const char t_html[];
	extern const char t_head[];
	extern const char t_body[];
	extern const char t_div[];
	extern const char t_h1[];
	extern const char t_h2[];
	extern const char t_h3[];
	extern const char t_script[];
	extern const char t_a[];

	typedef tag<t_html> html;
	typedef tag<t_head> head;
	typedef tag<t_body> body;
	typedef tag<t_div> div;
	typedef tag<t_h1> h1;
	typedef tag<t_h2> h2;
	typedef tag<t_h3> h3;
	typedef tag<t_script> script;
	typedef tag<t_a> a;
}

#endif // ENGINE_H
