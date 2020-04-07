/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>
#include <curl/curl.h>

#include <teabot_struct.h>
#include <classes/TeaBot/Exe.hpp>

char *api_baseurl;
size_t api_baseurl_length;
extern teabot_struct teabot;

namespace TeaBot {

typedef struct {
    char *data;
    size_t size;
    size_t allocated;
} MemoryStruct;
static char *curl_post(char *url, char *data);

char *Exe::post(std::string method, std::string data)
{
    char *ret, *url = (char *)malloc(
        sizeof(char) * (strlen(method.c_str()) + api_baseurl_length + 3));
    sprintf(url, "%s/%s", api_baseurl, method.c_str());
    ret = curl_post(url, (char *)(data.c_str()));
    free(url);
    return ret;
}

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

static char *curl_post(char *url, char *data)
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

}  // namespace TeaBot
