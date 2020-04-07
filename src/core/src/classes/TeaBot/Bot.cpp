/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */

#include <iostream>
#include <cstdio>
#include <string>

#include <macros.hpp>
#include <classes/Bot.hpp>
#include <classes/ResponseRoutes.hpp>

namespace TeaBot {

using json = nlohmann::json;

Bot::Bot(std::string payload)
{
    in = json::parse(payload);
}

bool Bot::validate_payload()
{
    if (isset(in["message"]) && isset(in["update_id"])) {
        return true;
    } else {
        return false;
    }
}

void Bot::execute()
{
    if (this->validate_payload()) {
        ResponseRoutes *res = new ResponseRoutes(this);
        res->execute();
    }
}

} // namespace TeaBot
