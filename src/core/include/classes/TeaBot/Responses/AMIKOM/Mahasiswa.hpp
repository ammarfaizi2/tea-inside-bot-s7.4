/**
* @author Ammar Faizi <ammarfaizi2@gmail.com>
* @version 7.4.0
* @license MIT
*/
#ifndef TEABOT__RESPONSES__AMIKOM__MAHASISWA_HPP
#define TEABOT__RESPONSES__AMIKOM__MAHASISWA_HPP

#include <teabot_struct.h>
#include <classes/TeaBot/ResponseRoutes.hpp>

extern teabot_struct teabot;

namespace TeaBot::Responses::AMIKOM {

class Mahasiswa
{
private:
  route_pass &r;
  char *exec(char *url);
public:
  Mahasiswa(route_pass &_r);
  bool login();
  char *getProfile();
};

};

#endif
