/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <curl/curl.h>
#include <teabot_struct.h>
#include <classes/TeaBot/Bot.hpp>
#include <classes/TeaBot/ResponseRoutes.hpp>

using namespace TeaBot;

extern char *api_baseurl;
extern teabot_struct teabot;
extern size_t api_baseurl_length;

extern "C" {

void init_daemon()
{
  ResponseRoutes::initRoutes();
  curl_global_init(CURL_GLOBAL_DEFAULT);
  #define TELEGRAM_API_BASEURL "https://api.telegram.org/bot%s"
  api_baseurl = (char *)malloc(sizeof(TELEGRAM_API_BASEURL) + strlen(teabot.token) + 2);
  sprintf(api_baseurl, TELEGRAM_API_BASEURL, teabot.token);
  #undef TELEGRAM_API_BASEURL
  api_baseurl_length = strlen(api_baseurl);
  printf("storage_path: \"%s\"\n", teabot.storage_path);
}

void *execute_payload(char *payload)
{  
  Bot *st = new Bot(std::string(payload));
  st->execute();
  delete st;
  free(payload);
  return NULL;
}

}
