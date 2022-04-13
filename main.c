#include <stdio.h>
#include <stdarg.h>

#include "lang.h"

void error(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
}

void print(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}

int main(int argc, char *argv[])
{
  char buffer[1024];
  while(!feof(stdin)) {
    printf("> ");
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);
    eval(buffer);
  }
  return 0;
}
