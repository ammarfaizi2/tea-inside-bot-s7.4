/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>

#include <macros.hpp>
#include <my_curl.hpp>
#include <classes/TeaBot/Exe.hpp>
#include <classes/TeaBot/Responses/Start.hpp>
#include <classes/TeaBot/Responses/AMIKOM/Mahasiswa.hpp>

#define API_BASE_URL "http://127.0.0.1:8000"
#define BASE_END API_BASE_URL"/api.php?type=mahasiswa&act=%s&nim=%s&pass=%s%s"

extern teabot_struct teabot;

namespace TeaBot::Responses::AMIKOM {

using namespace TeaBot;

Mahasiswa::Mahasiswa(route_pass &_r): r(_r)
{
  std::cout << "Mahasiswa constructor\n";
  #define init_dir(A) \
    std::cout << "test: \"" << A << "\"" << std::endl; \
    if (access(A, F_OK) == -1) { \
      mkdir(A, 0750); \
    }

  std::cout << "token: " << teabot.token << std::endl;
  init_dir(teabot.storage_path);
  init_dir(teabot.amikom_storage_path);
  init_dir(teabot.amikom_storage_mhs_path);

  // #undef init_dir
}

bool Mahasiswa::login()
{
  json d;
  char *res;
  char url[sizeof(BASE_END) * 2];

  sprintf(url, BASE_END, "login", r.match.r[1], r.match.r[2], "");
  res = this->exec(url);
  d = json::parse(res);
  free(res);

  if (isset(d["res"]) && isset(d["res"]["token"])) {
    res = Exe::post("sendMessage",
      json({
        {"chat_id", r.res.bot->ind->chat_id},
        {"reply_to_message_id", r.res.bot->ind->msg_id},
        {"text", "Login Success!"}
      }).dump()
    );
    free(res);

    json p;
    std::string caption = "";
    res = this->getProfile();
    p = json::parse(res);
    free(res);

    if (
      isset(p["res"]) && isset(p["res"]["Mhs"]) &&
      isset(p["res"]["PeriodeAkademik"]) &&
      isset(p["res"]["Mhs"]["Npm"]) &&
      isset(p["res"]["Mhs"]["Nama"]) &&
      isset(p["res"]["Mhs"]["Angkatan"]) &&
      isset(p["res"]["Mhs"]["EmailAmikom"]) &&
      isset(p["res"]["Mhs"]["NpmImg"]) &&
      isset(p["res"]["PeriodeAkademik"]["TahunAkademik"]) &&
      isset(p["res"]["PeriodeAkademik"]["Semester"])
    ) {
      #define stdf(A) std::string(A)
      caption += 
        "<b>[Profil]</b>"
        "\n<b>NIM: </b>"+stdf(p["res"]["Mhs"]["Npm"])+
        "\n<b>Nama: </b>"+stdf(p["res"]["Mhs"]["Nama"])+
        "\n<b>Angkatan: </b>"+stdf(p["res"]["Mhs"]["Angkatan"])+
        "\n<b>Email: </b>"+stdf(p["res"]["Mhs"]["EmailAmikom"])+
        "\n<b>Periode Akademik: </b> "+stdf(p["res"]["PeriodeAkademik"]["TahunAkademik"])+
        "\n<b>Semester: </b>"+(std::to_string(p["res"]["PeriodeAkademik"].value("Semester", 0)));

      res = Exe::post("sendPhoto",
        json({
          {"chat_id", r.res.bot->ind->chat_id},
          {"reply_to_message_id", r.res.bot->ind->msg_id},
          {"caption", caption},
          {"photo", p["res"]["Mhs"]["NpmImg"]},
          {"parse_mode", "HTML"}
        }).dump()
      );
    } else {
    }
  } else {

  }

  return true;
}


char *Mahasiswa::getProfile()
{
  json d;
  char url[sizeof(BASE_END) * 2];
  sprintf(url, BASE_END, "profile", r.match.r[1], r.match.r[2], "");
  return this->exec(url);
}

char *Mahasiswa::exec(char *url)
{
  char *ret;
  CURL *curl;
  CURLcode res;
  struct curl_slist *chunk = NULL;
  MemoryStruct mem;

  debug_log(5, "Curl to URL: %s", url);

  curl = curl_easy_init();
  if (!curl) {
      ret = NULL;
      goto ret;
  }

  mem.data = (char *)malloc(sizeof(char) * 2048);
  mem.size = 0;
  mem.allocated = 2048;

  chunk = curl_slist_append(chunk, "Content-Type: application/json");
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&mem);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
    (void (*)(void*, size_t, size_t, void *))WriteMemoryCallback);

  res = curl_easy_perform(curl);
  if (res == CURLE_OK) {
    ret = mem.data;
    ret[mem.size] = 0;
  } else {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    free(mem.data);
    ret = NULL;
  }

ret:
  if (curl != NULL) {
    curl_easy_cleanup(curl);
  }
  if (chunk != NULL) {
    curl_slist_free_all(chunk);
  }
  return ret;
}

} // namespace TeaBot::Responses::AMIKOM
