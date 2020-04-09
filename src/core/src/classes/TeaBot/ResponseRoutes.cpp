/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>

#include <macros.hpp>
#include <classes/TeaBot/ResponseRoutes.hpp>
#include <classes/TeaBot/Responses/Start.hpp>
#include <classes/TeaBot/Responses/AMIKOM/Mahasiswa.hpp>

namespace TeaBot {

using json = nlohmann::json;
using namespace TeaBot::Responses;
using namespace TeaBot::Responses::AMIKOM;

routes rts[4];
#define routes_amt (sizeof(rts)/sizeof(rts[0]))

ResponseRoutes::ResponseRoutes(Bot *bot)
{
  this->bot = bot;
  if (isset(bot->in["message"]["text"])) {
    text = bot->in["message"]["text"];
    msg_type = msg_text;
  } else {
    text = "";
  }
}

void ResponseRoutes::execute()
{
  route_pass r(*this);
  for (uint8_t i = 0; i < routes_amt; i++) {

    if (!rts[i].pat) continue;

    if (my_pcre_find(rts[i].pat,
      (const unsigned char *)(text.c_str()), &(r.match))) {
      bool ret = rts[i].handler(r);
      my_pcre_res_destroy(&(r.match));
      if (ret) {
        break;
      }
    }
  }
}

void ResponseRoutes::initRoutes()
{
  debug_log(2, "Initializing routes...\n");

  rts[0].pat = mp_compile("^\\/debug", 0);
  rts[0].handler = [](route_pass &r){
    Start *st = new Start(r);
    bool ret = st->run();
    delete st;
    return ret;
  };

  rts[1].pat = mp_compile(
    "^(?:\\\\|\\.|\\!)?amikom\\s+login\\s(.+)\\s(.+)",
    PCRE2_CASELESS | PCRE2_MULTILINE);
  rts[1].handler = [](route_pass &r) {
    Mahasiswa *st = new Mahasiswa(r);
    bool ret = st->login();
    delete st;
    return ret;
  };

  rts[2].pat = mp_compile(
    "^(?:\\\\|\\.|\\!)?jadwal(?:\\s+)?(senin|selasa|rabu|kamis|jum'?at|sabtu|minggu)?$",
    PCRE2_CASELESS | PCRE2_MULTILINE);
  rts[2].handler = [](route_pass &r) {
    if (r.match.count > 1) {
      strtoupper(r.match.r[1], strlen(r.match.r[1]));
      if (!strcmp(r.match.r[1], "JUM'AT")) {
        strcpy(r.match.r[1], "JUMAT");
      }
    }
    Mahasiswa *st = new Mahasiswa(r);
    bool ret = st->jadwal();
    delete st;
    return ret;
  };

  rts[3].pat = mp_compile("^(?:\\\\|\\.|\\!)?dqc$", PCRE2_CASELESS);
  rts[3].handler = [](route_pass &r) {
    Mahasiswa *st = new Mahasiswa(r);
    bool ret = st->listPresensi();
    delete st;
    return ret;
  };
}

} // namespace TeaBot
