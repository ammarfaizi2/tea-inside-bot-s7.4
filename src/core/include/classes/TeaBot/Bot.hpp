/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#ifndef TEABOT__BOT_HPP
#define TEABOT__BOT_HPP

#include <string>
#include <stdint.h>
#include <nlohmann/json.hpp>

namespace TeaBot {

using json = nlohmann::json;

struct _ind {
	int64_t chat_id;
	uint64_t user_id;
  uint64_t msg_id;
  _ind(
    int64_t _chat_id,
    uint64_t _user_id,
    uint64_t _msg_id
  );
};

class Bot
{
private:
  bool validate_payload();
public:
  struct _ind *ind;
  json in;
  Bot(std::string payload);
  void execute();
};

} // namespace Bot.hpp

#endif
