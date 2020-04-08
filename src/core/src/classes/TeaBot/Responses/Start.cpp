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
  char *test = Exe::post("sendMessage", json(
    {
      {"chat_id", r.res.bot->ind->chat_id},
      {"reply_to_message_id", r.res.bot->ind->msg_id},
      {"text", r.res.bot->in.dump(2)}
    }
  ).dump());
  std::cout << test << std::endl;
  free(test);
  return true;
}

} // namespace TeaBot::Responses
