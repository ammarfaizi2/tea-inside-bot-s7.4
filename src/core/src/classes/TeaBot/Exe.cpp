/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */

#include <iostream>
#include <cstdio>
#include <string>

#include <classes/TeaBot/Exe.hpp>

#ifndef TEABOT_STRUCT_H
#define TEABOT_STRUCT_H

typedef struct {
    char *token;
    char *bot_username;
} teabot_struct;

#endif

extern teabot_struct teabot;

namespace TeaBot {

using json = nlohmann::json;

Exe::post(std::string method, json data)
{
}

}  // namespace TeaBot
