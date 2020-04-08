/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#ifndef TEABOT__RESPONSE_ROUTES_HPP
#define TEABOT__RESPONSE_ROUTES_HPP

#include <string>
#include <my_pcre.h>
#include <classes/TeaBot/Bot.hpp>

namespace TeaBot {

using json = nlohmann::json;

typedef enum {
  msg_text = (0 << 1),
  msg_photo = (0 << 2),
  msg_video = (0 << 3),
  msg_sticker = (0 << 4),
  msg_voice = (0 << 5)
} msg_type_enum;

class ResponseRoutes
{
public:
  Bot *bot;
  std::string text;
  msg_type_enum msg_type;
  static void initRoutes();
  ResponseRoutes(Bot *bot);
  void execute();
};

typedef struct _route_pass {
  ResponseRoutes &res;
  pcre_res match;
  _route_pass(ResponseRoutes &_r): res(_r) {}
} route_pass;

typedef struct {
  pcre2_code *pat;
  std::function<bool(route_pass &)> handler;
} routes;

} // namespace Bot.hpp

#endif
