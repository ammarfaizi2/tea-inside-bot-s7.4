
#include <stdio.h>
#include <stdarg.h>

#define DEBUGGER_CPP
#include <macros.hpp>

#ifdef ICETEA_DEBUG

int8_t verbose_level;

/**
 * Print debug log.
 *
 * It will be called by macro debug_log.
 */
void internal_teaserver_debug_log(const char *format, ...)
{
  va_list argp;

  va_start(argp, format);
  vfprintf(stdout, format, argp);
  va_end(argp);
  fflush(stdout);
}

#endif
