/**
* @author Ammar Faizi <ammarfaizi2@gmail.com>
* @version 7.4.0
* @license MIT
*/
#ifndef TEABOT__RESPONSES__AMIKOM__MAHASISWA_HPP
#define TEABOT__RESPONSES__AMIKOM__MAHASISWA_HPP

#include <classes/TeaBot/ResponseRoutes.hpp>

namespace TeaBot::Responses::AMIKOM {

class Mahasiswa
{
private:
  route_pass &r;
public:
  Mahasiswa(route_pass &_r);
  bool login();
};

};

#endif
