
#ifndef MY_PCRE_H
#define MY_PCRE_H

#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <string.h>
#include <pcre2.h>

typedef struct {
    int count;
    char **r;
} pcre_res;

typedef struct {
    int count;
    pcre_res *r;
} pcre_res_all;

void my_pcre_res_destroy(pcre_res *result);
pcre2_code *my_pcre_compile(const unsigned char *pattern);
int my_pcre_find(pcre2_code *re, const unsigned char *subject, pcre_res* result);

#define mp_compile(A) my_pcre_compile((const unsigned char *)A)

#endif
