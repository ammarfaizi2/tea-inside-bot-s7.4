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

#define stdf(A) std::string(A)
#define stdft(A) std::to_string(A)
#define API_BASE_URL "http://127.0.0.1:8000"
#define BASE_END API_BASE_URL"/api.php?type=mahasiswa&act=%s&nim=%s&pass=%s%s"

extern teabot_struct teabot;

namespace TeaBot::Responses::AMIKOM {

using namespace TeaBot;

Mahasiswa::Mahasiswa(route_pass &_r): r(_r)
{
  #define init_dir(A) \
    if (access(A, F_OK) == -1) { \
      mkdir(A, 0750); \
    }

  init_dir(teabot.storage_path);
  init_dir(teabot.amikom_storage_path);
  init_dir(teabot.amikom_storage_mhs_path);

  userdir = (char *)malloc(
    sizeof(char) * 
    (strlen(teabot.amikom_storage_mhs_path) + 22)
  );
  nimfile = (char *)malloc(
    sizeof(char) * 
    (strlen(teabot.amikom_storage_mhs_path) + 22 + sizeof("/nim"))
  );
  passfile = (char *)malloc(
    sizeof(char) * 
    (strlen(teabot.amikom_storage_mhs_path) + 22 + sizeof("/pass"))
  );

  sprintf(userdir, "%s/%ld", teabot.amikom_storage_mhs_path,
    r.res.bot->ind->user_id);
  sprintf(nimfile, "%s/nim", userdir);
  sprintf(passfile, "%s/pass", userdir);
  init_dir(userdir);

  if (access(nimfile, F_OK) != -1) {
    FILE *handle = fopen(nimfile, "r");
    nim = (char *)malloc(sizeof("xx.xx.xxxx") + 1);
    if ((handle != NULL) && (!fgets(nim, sizeof("xx.xx.xxxx"), handle))) {
      nim = NULL;
    }
    fclose(handle);
  }

  if (access(passfile, F_OK) != -1) {
    FILE *handle = fopen(passfile, "r");
    pass = (char *)malloc(9);
    if ((handle != NULL) && (!fgets(pass, 8, handle))) {
      pass = NULL;
    }
    fclose(handle);
  }
  #undef init_dir
}

Mahasiswa::~Mahasiswa()
{
  free(this->userdir);
  free(this->nimfile);
}

bool Mahasiswa::jadwal()
{
  char *res;
  if (this->hasLoggedIn()) {
    char url[sizeof(BASE_END) * 2];
    sprintf(url, BASE_END, "jadwal", nim, pass, "");
    res = this->exec(url);
    json d = json::parse(res);
    free(res);
    if (isset(d["res"]) && d["res"].is_array()) {
      int size = d["res"].size();
      std::string fixde = "<b>Jadwal</b>\n", last_day = "";
      for (int i = 0; i < size; i++) {
        if (isset(d["res"][i])) {
          auto dr = d["res"][i].get_ref<json::object_t &>();
          if (isset(dr["Hari"]) &&
              (
                (r.match.count == 1) ||
                (!strcmp(dr["Hari"].get_ref<json::string_t &>().c_str(), r.match.r[1]))
              ) &&
              isset(dr["IdKuliah"]) &&
              isset(dr["JenisKuliah"]) &&
              isset(dr["Jenjang"]) &&
              isset(dr["Kelas"]) &&
              isset(dr["Keterangan"]) &&
              isset(dr["Kode"]) &&
              isset(dr["MataKuliah"]) &&
              isset(dr["NamaDosen"]) &&
              isset(dr["Nik"]) &&
              isset(dr["Ruang"]) &&
              isset(dr["Waktu"])
          ) {
            if (last_day != dr["Hari"]) {
              fixde += "\n<b>"+stdf(d["res"][i]["Hari"])+":</b>\n";
              last_day = dr["Hari"];
            }
            fixde += 
              "["+stdft(d["res"][i].value("IdKuliah", 0))+"]\n"
              "<b>Mata Kuliah: </b>"+stdf(dr["MataKuliah"])+"\n"
              "<b>Keterangan: </b>"+stdf(dr["Keterangan"])+"\n"
              "<b>Ruang: </b>"+stdf(dr["Ruang"])+"\n"
              "<b>Waktu: </b>"+stdf(dr["Waktu"])+"\n"
              "<b>Kelas: </b>"+stdf(dr["Kelas"])+"\n"
              "<b>NIK: </b>"+stdf(dr["Nik"])+"\n"
              "<b>Nama Dosen: </b>"+stdf(dr["NamaDosen"])+"\n--\n";
          }
        }
      }

      res = Exe::post("sendMessage",
        json({
          {"chat_id", r.res.bot->ind->chat_id},
          {"reply_to_message_id", r.res.bot->ind->msg_id},
          {"text", fixde},
          {"parse_mode", "HTML"}
        }).dump()
      );
      free(res);
    }
  }

  return true;
}

bool Mahasiswa::listPresensi()
{
  if (this->hasLoggedIn()) {
    json d;
    char *res, url[sizeof(BASE_END) * 2];
    sprintf(url, BASE_END, "list_presensi", nim, pass, "");
    res = this->exec(url);
    d = json::parse(res);
    free(res);

    if (isset(d["res"]) && d["res"].is_array()) {
      int size = d["res"].size();
      std::string fixde = "<b>Data Presensi "+std::string(nim)+"</b>";
      for (int i = 0; i < size; i++) {
        if (isset(d["res"][i])) {
          auto dr = d["res"][i].get_ref<json::object_t &>();
          if (isset(dr["KrsId"]) && isset(dr["Kode"]) &&
              isset(dr["NamaMk"]) && isset(dr["JmlSks"]) &&
              isset(dr["JmlPresensiKuliah"]) &&
              isset(dr["IsHadirMID"]) && isset(dr["IsHadirUAS"])
          ) {
            fixde +=
              "\n\n<b>["+stdft(d["res"][i].value("KrsId", 0))+" "+stdf(dr["Kode"])+"]</b>\n"
              "("+stdft(d["res"][i].value("JmlSks", 0))+" SKS) "+stdf(dr["NamaMk"])+"\n"
              "[Presensi: "+stdft(d["res"][i].value("JmlPresensiKuliah", 0))+"] "
              "[UTS: "+stdft(d["res"][i].value("IsHadirMID", 0))+"] "
              "[UAS: "+stdft(d["res"][i].value("IsHadirUAS", 0))+"]";
          }
        }
      }

      res = Exe::post("sendMessage",
        json({
          {"chat_id", r.res.bot->ind->chat_id},
          {"reply_to_message_id", r.res.bot->ind->msg_id},
          {"text", fixde},
          {"parse_mode", "HTML"}
        }).dump()
      );
      free(res);
    }
  }
  return true;
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
      res = Exe::post("sendMessage",
        json({
          {"chat_id", r.res.bot->ind->chat_id},
          {"reply_to_message_id", r.res.bot->ind->msg_id},
          {"text", "Cannot retrieve profile info!"}
        }).dump()
      );
      free(res);
    }

    FILE *handle = fopen(nimfile, "w");
    fputs(r.match.r[1], handle);
    fclose(handle);

    handle = fopen(passfile, "w");
    fputs(r.match.r[2], handle);
    fclose(handle);

  } else {
    res = Exe::post("sendMessage",
      json({
        {"chat_id", r.res.bot->ind->chat_id},
        {"reply_to_message_id", r.res.bot->ind->msg_id},
        {"text", "Login Failed!"}
      }).dump()
    );
    free(res);
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

bool Mahasiswa::hasLoggedIn()
{
  if (nim == NULL) {
    char *res = Exe::post("sendMessage",
      json({
        {"chat_id", r.res.bot->ind->chat_id},
        {"reply_to_message_id", r.res.bot->ind->msg_id},
        {"text", "You have not logged in yet!"}
      }).dump()
    );
    free(res);
    return false;
  }
  return true;
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
    (void (*)(void *, size_t, size_t, void *))WriteMemoryCallback);

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

