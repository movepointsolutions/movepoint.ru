#include <stdexcept>
#include "snippet.h"

snippet::snippet(const std::string &filename)
	: file(filename)
{
    string << file.rdbuf();
    if (content().empty())
        throw std::runtime_error(filename + " not found");
}

std::string snippet::content() const
{
	return string.str();
}
