#include "snippet.h"

snippet::snippet(const std::string &filename)
	: file(filename)
{
    string << file.rdbuf();
}

std::string snippet::content() const
{
	return string.str();
}
