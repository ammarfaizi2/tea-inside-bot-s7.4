/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#include <iostream>

#include <classes/TeaBot/Responses/Start.hpp>
#include <macros.hpp>

namespace TeaBot::Responses {

Start::Start(route_pass &_r): r(_r)
{
}

bool Start::run()
{
    std::cout << "text: " << r.res.text << std::endl;
    return true;
}

} // namespace TeaBot::Responses
