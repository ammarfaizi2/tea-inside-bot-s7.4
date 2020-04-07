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

class Exe
{
public:
    static char *post(std::string method, std::string data);
};

} // namespace TeaBot

#endif
