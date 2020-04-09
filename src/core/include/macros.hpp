
#ifndef MY_MACROS_HPP
#define MY_MACROS_HPP

#define isset(A) (A != nullptr)

#ifdef ICETEA_DEBUG

#include <time.h>
#include <stdio.h>
#include <stdint.h>
void internal_teaserver_debug_log(const char *format, ...);

#ifndef DEBUGGER_CPP
extern int8_t verbose_level;
#endif

__attribute__((always_inline)) inline static char *__internal_get_rawtime()
{
  char *timestr;
  time_t rawtime;
  time(&rawtime);
  timestr = asctime(localtime(&rawtime));
  timestr[24] = '\0';
  return timestr;
}

#define PPCAT_NX(A, B, C) A B C

#define debug_log(VLEVEL, FORMAT, ...) \
  if (VLEVEL <= verbose_level) { \
    internal_teaserver_debug_log( \
      PPCAT_NX("[%s] ", FORMAT, "\n"), \
        __internal_get_rawtime(), \
        ##__VA_ARGS__ \
    ); \
  }
#else
#define debug_log(...)
#endif

#endif
