/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#ifndef TEABOT__EXE_HPP
#define TEABOT__EXE_HPP

#include <string>
#include <stdint.h>

namespace TeaBot {

using json = nlohmann::json;

class Exe
{
public:
    static void post(std::string method, json data);
};

} // namespace TeaBot

#endif
