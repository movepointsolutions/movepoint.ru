#ifndef SNIPPET_H
#define SNIPPET_H

#include <fstream>
#include <sstream>
#include <string>

class snippet
{
	std::ifstream file;
	std::ostringstream string;
public:
	snippet(const std::string &filename);
	std::string content() const;
};

#endif // SNIPPET_H
