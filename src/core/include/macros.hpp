
#ifndef MY_MACROS_HPP
#define MY_MACROS_HPP

#define isset(A) (A != nullptr)

#ifdef ICETEA_DEBUG

#include <stdio.h>
#include <stdint.h>
void internal_teaserver_debug_log(const char *format, ...);
extern int8_t verbose_level;

__attribute__((always_inline)) inline static char *__internal_get_rawtime()
{
  char *timestr;
  time_t rawtime;
  time(&rawtime);
  timestr = asctime(localtime(&rawtime));
  timestr[24] = '\0';
  return timestr;
}

#define debug_log(VLEVEL, FORMAT, ...) \
  if (VLEVEL <= verbose_level) { \
    internal_teaserver_debug_log( \
      "[]: "FORMAT"\n", \
        __internal_get_rawtime(), \
        ##__VA_ARGS__ \
    ); \
  }
#endif

#endif
