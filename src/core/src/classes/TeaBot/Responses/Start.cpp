/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#include <iostream>

#include <macros.hpp>
#include <classes/TeaBot/Exe.hpp>
#include <classes/TeaBot/Responses/Start.hpp>

namespace TeaBot::Responses {

using namespace TeaBot;

Start::Start(route_pass &_r): r(_r)
{
}

bool Start::run()
{
    json d = {
        {"chat_id", -1001226735471},
        {"reply_to_message_id", 122},
        {"text", ""}
    };
    char *test = Exe::post("sendMessage", d.dump());
    std::cout << test << std::endl;
    free(test);
    return true;
}

} // namespace TeaBot::Responses
