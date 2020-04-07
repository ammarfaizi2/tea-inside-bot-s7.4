/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */

#include <iostream>
#include <cstdio>
#include <string>

#include <macros.hpp>
#include <classes/ResponseRoutes.hpp>

namespace TeaBot {

using json = nlohmann::json;

ResponseRoutes::ResponseRoutes(Bot *bot)
{
    this->bot = bot;
    if (isset(bot->in["message"]["text"])) {
        text = bot->in["message"]["text"];
        msg_type = msg_text;
    } else {
        text = "";
    }
}

void ResponseRoutes::execute()
{
    std::cout << text;
}

} // namespace TeaBot
