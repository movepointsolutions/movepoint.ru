#include <iostream>
#include <stdexcept>
#include "invite.h"
#include "redis.h"
#include "engine.h"

using namespace std::string_literals;

Invite::Invite()
{
}

std::string Invite::issue() const
{
    Redis redis;
    redis.hit();
    tags::h2 h2;
    h2.innerhtml("Invite");
    tags::h3 invite;
#include "page.view"
    return page_view(true, h2.content() + s_inviteform.content());
}
