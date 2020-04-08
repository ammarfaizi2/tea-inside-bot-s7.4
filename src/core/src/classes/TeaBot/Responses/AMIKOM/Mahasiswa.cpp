/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#include <iostream>

#include <macros.hpp>
#include <classes/TeaBot/Exe.hpp>
#include <classes/TeaBot/Responses/Start.hpp>
#include <classes/TeaBot/Responses/AMIKOM/Mahasiswa.hpp>

namespace TeaBot::Responses::AMIKOM {

using namespace TeaBot;

Mahasiswa::Mahasiswa(route_pass &_r): r(_r)
{
}

bool Mahasiswa::login()
{
  std::cout << "Login\n"
    << "Count: " << r.match.count << "\n"
    << r.match.r[1] << "\n"
    << r.match.r[2] << "\n";
  return true;
}

} // namespace TeaBot::Responses::AMIKOM
