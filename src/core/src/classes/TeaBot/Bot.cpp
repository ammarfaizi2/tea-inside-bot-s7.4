/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */

#include <iostream>
#include <cstdio>
#include <string>

#include <macros.hpp>
#include <classes/TeaBot/Bot.hpp>
#include <classes/TeaBot/ResponseRoutes.hpp>

namespace TeaBot {

using json = nlohmann::json;

Bot::Bot(std::string payload)
{
  in = json::parse(payload);
}

bool Bot::validate_payload()
{

  if (!(
    isset(in["update_id"]) &&
    isset(in["message"]) &&
    isset(in["message"]["chat"]) &&
    isset(in["message"]["chat"]["id"]) &&
    isset(in["message"]["from"]) &&
    isset(in["message"]["from"]["id"]) &&
    isset(in["message"]["message_id"])
  )) {

    // Debug only.
    std::cout << "Invalid payload" << std::endl;

    goto ret_fal;
  } else {
    // Debug only.
    std::cout 
      << "\nChat ID: " << in["message"]["chat"]["id"]
      << "\nUser ID: " << in["message"]["from"]["id"]
      << std::endl;
  }

  ind = new _ind(
    in["message"]["chat"]["id"],
    in["message"]["from"]["id"],
    in["message"]["message_id"]
  );

  return true;

ret_fal:
  return false;
}

_ind::_ind(
  int64_t _chat_id,
  uint64_t _user_id,
  uint64_t _msg_id
): chat_id(_chat_id), user_id(_user_id), msg_id(_msg_id)
{}

void Bot::execute()
{
  if (this->validate_payload()) {
    ResponseRoutes *res = new ResponseRoutes(this);
    res->execute();
    delete res;
  }
}

} // namespace TeaBot
