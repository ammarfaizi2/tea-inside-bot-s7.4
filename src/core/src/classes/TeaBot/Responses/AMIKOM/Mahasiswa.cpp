/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#include <iostream>

#include <macros.hpp>
#include <my_curl.hpp>
#include <classes/TeaBot/Exe.hpp>
#include <classes/TeaBot/Responses/Start.hpp>
#include <classes/TeaBot/Responses/AMIKOM/Mahasiswa.hpp>

namespace TeaBot::Responses::AMIKOM {

using namespace TeaBot;

Mahasiswa::Mahasiswa(route_pass &_r): r(_r) {}

char *Mahasiswa::exec(char *url)
{
  char *ret;
  CURL *curl;
  CURLcode res;
  struct curl_slist *chunk = NULL;
  MemoryStruct mem;

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
  curl_easy_setopt(curl, CURLOPT_POST, 1);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
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

bool Mahasiswa::login()
{
  std::cout << "Login\n"
    << "Count: " << r.match.count << "\n"
    << r.match.r[1] << "\n"
    << r.match.r[2] << "\n";
  return true;
}

} // namespace TeaBot::Responses::AMIKOM
