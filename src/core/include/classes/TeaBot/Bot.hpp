/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#ifndef TEABOT__BOT_HPP
#define TEABOT__BOT_HPP

#include <string>
#include <nlohmann/json.hpp>

namespace TeaBot {

using json = nlohmann::json;

class Bot
{
private:
    bool validate_payload();
public:
    json in;
    Bot(std::string payload);
    void execute();
};

} // namespace Bot.hpp

#endif
