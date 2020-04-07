/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>

#include <macros.hpp>
#include <classes/ResponseRoutes.hpp>

namespace TeaBot {

using json = nlohmann::json;

routes rts[3];
#define routes_amt (sizeof(rts)/sizeof(rts[0]))

void ResponseRoutes::initRoutes()
{
    rts[0].pat = mp_compile("^\\/debug");
    rts[0].handler = [](ResponseRoutes *res){
        std::cout << res->text << std::endl;
        return true;
    };
}

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
    rts[0].handler(this);
}

} // namespace TeaBot
