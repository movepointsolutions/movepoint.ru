#ifndef FORM_PART_H
#define FORM_PART_H

#include <string>

class form_part
{
    std::string type_;
    std::string disposition_;
    std::string name_;
    std::string filename_;

public:
    form_part(const std::string &);
    std::string type() const;
    std::string disposition() const;
    std::string name() const;
    std::string filename() const;
};

#endif // FORM_PART_H
