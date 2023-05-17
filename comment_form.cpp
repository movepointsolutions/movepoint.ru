#include "comment_form.h"
#include "engine.h"
#include "redis.h"

using namespace std::string_literals;

/*static std::string elem(const std::string &label, const std::string &type)
{
    tags::label label;
    label.push_attr("for", type);
}*/

std::string CommentForm::content(long long session)
{
    static Redis redis;
    std::string login{redis.session_login(session)};
    std::string dn{redis.display_name(login)};
    tags::h3 h3;
    h3.innerhtml("Обсудим?");
    tags::div group;
    group.push_attr("class", "form-group");
    tags::form form;
    form.push_attr("action", "/");
    form.push_attr("method", "post");
    if (!login.empty())
        form.push_attr("enctype", "multipart/form-data");
    
    const std::string ctl1 = [&dn](){
        tags::label label;
        label.push_attr("for", "nickname");
        label.innerhtml("Nickname (*)");
        tags::input input;
        input.push_attr("class", "form-control");
        input.push_attr("type", "text");
        input.push_attr("id", "nickname");
        input.push_attr("name", "nickname");
        if (!dn.empty())
            input.push_attr("value", dn);
        return label.content() + input.content();
    }();
    
    const std::string ctl2 = [](){
        tags::label label;
        label.push_attr("for", "text");
        label.innerhtml("Text (*)");
        tags::textarea textarea;
        textarea.push_attr("class", "form-control");
        textarea.push_attr("id", "text");
        textarea.push_attr("name", "text");
        return label.content() + textarea.content();
    }();

    const std::string ctl3 = [&login](){
        if (login.empty())
            return ""s;
        tags::label label;
        label.push_attr("for", "file");
        label.innerhtml("File");
        tags::input input;
        input.push_attr("class", "form-control");
        input.push_attr("type", "file");
        input.push_attr("id", "file");
        input.push_attr("name", "file");
        return label.content() + input.content();
    }();
    
    const std::string ctl4 = [](){
        tags::button button;
        button.push_attr("class", "form-control");
        button.push_attr("type", "submit");
        button.push_attr("name", "submit");
        button.push_attr("value", "Send");
        button.innerhtml("Send");
        return button.content();
    }();
    form.innerhtml(ctl1 + ctl2 + ctl3 + ctl4);

    group.innerhtml(form.content());
    return h3.content() + group.content();
}
