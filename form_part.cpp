#include <sstream>
#include <iostream>
#include "form_part.h"

form_part::form_part(const std::string &buf)
{
    const auto he = buf.find("\r\n\r\n");
    const auto headers = buf.substr(0, he + 2);
    const auto file = buf.substr(he + 4);
    std::istringstream H(headers);
    std::cout << "HDRS" << H.rdbuf() << std::endl;
    std::cout << "FILE" << file.size() << std::endl;
}

std::string form_part::type() const
{
    return type_;
}

std::string form_part::disposition() const
{
    return disposition_;
}

std::string form_part::name() const
{
    return name_;
}

std::string form_part::filename() const
{
    return filename_;
}
