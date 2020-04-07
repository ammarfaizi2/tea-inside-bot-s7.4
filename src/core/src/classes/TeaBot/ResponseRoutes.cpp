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
#include <classes/TeaBot/ResponseRoutes.hpp>
#include <classes/TeaBot/Responses/Start.hpp>

namespace TeaBot {

using json = nlohmann::json;
using namespace TeaBot::Responses;

routes rts[3];
#define routes_amt (sizeof(rts)/sizeof(rts[0]))

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
    route_pass r(*this);
    for (uint8_t i = 0; i < routes_amt; i++) {
        if (my_pcre_find(rts[i].pat,
            (const unsigned char *)(text.c_str()), &(r.match))) {
            if (rts[i].handler(r)) {
                break;
            }
            my_pcre_res_destroy(&(r.match));
        }
    }
}

void ResponseRoutes::initRoutes()
{
    rts[0].pat = mp_compile("^\\/debug");
    rts[0].handler = [](route_pass &r){
        Start *st = new Start(r);
        bool ret = st->run();
        delete st;
        return ret;
    };
}

} // namespace TeaBot
