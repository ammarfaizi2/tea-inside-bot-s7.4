/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#ifndef TEABOT__RESPONSE_ROUTES_HPP
#define TEABOT__RESPONSE_ROUTES_HPP

#include <string>
#include <classes/Bot.hpp>

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
private:
    Bot *bot;
    std::string text;
    msg_type_enum msg_type;
public:
    ResponseRoutes(Bot *bot);
    void execute();
};

} // namespace Bot.hpp

#endif
