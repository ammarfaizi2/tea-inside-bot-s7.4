
#ifndef MY_CURL_HPP
#define MY_CURL_HPP

#include <string.h>
#include <curl/curl.h>

typedef struct {
  char *data;
  size_t size;
  size_t allocated;
} MemoryStruct;

static size_t
WriteMemoryCallback(char *contents, size_t size, size_t nmemb, MemoryStruct *userp)
{
  size_t realsize = size * nmemb;
  if ((userp->size + realsize) >= userp->allocated) {
      userp->allocated += 2048 + realsize;
      userp->data = (char *)realloc(userp->data, userp->allocated);
  }
  memcpy(&(userp->data[userp->size]), contents, realsize);
  userp->size += realsize;

  return realsize;
}

#endif
