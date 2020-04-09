/**
* @author Ammar Faizi <ammarfaizi2@gmail.com>
* @version 7.4.0
* @license MIT
*/
#ifndef TEABOT__RESPONSES__AMIKOM__MAHASISWA_HPP
#define TEABOT__RESPONSES__AMIKOM__MAHASISWA_HPP

#include <teabot_struct.h>
#include <classes/TeaBot/ResponseRoutes.hpp>

namespace TeaBot::Responses::AMIKOM {

class Mahasiswa
{
private:
  route_pass &r;
  char *userdir;
  char *nimfile;
  char *nim = NULL;
  char *exec(char *url);
public:
  Mahasiswa(route_pass &_r);
  ~Mahasiswa();
  bool login();
  char *getProfile();
};

};

#endif
