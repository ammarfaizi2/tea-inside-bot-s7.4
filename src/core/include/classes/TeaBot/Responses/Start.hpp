/**
* @author Ammar Faizi <ammarfaizi2@gmail.com>
* @version 7.4.0
* @license MIT
*/
#ifndef TEABOT__RESPONSES__START_HPP
#define TEABOT__RESPONSES__START_HPP

#include <classes/TeaBot/ResponseRoutes.hpp>

namespace TeaBot::Responses {
class Start
{
private:
    route_pass r;
public:
    Start(route_pass &_r);
    bool run();
};
} // namespace TeaBot::Responses

#endif
