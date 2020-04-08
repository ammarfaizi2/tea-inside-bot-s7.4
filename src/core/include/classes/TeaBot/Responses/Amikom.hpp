/**
* @author Ammar Faizi <ammarfaizi2@gmail.com>
* @version 7.4.0
* @license MIT
*/
#ifndef TEABOT__RESPONSES__AMIKOM_HPP
#define TEABOT__RESPONSES__AMIKOM_HPP

#include <classes/TeaBot/ResponseRoutes.hpp>

namespace TeaBot::Responses {
class Amikom
{
private:
  route_pass r;
public:
  Amikom(route_pass &_r);
  bool login();
};
} // namespace TeaBot::Responses

#endif
