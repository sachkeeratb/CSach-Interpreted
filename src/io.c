#include <stdio.h>
#include <stdlib.h>
#include "include/io.h"

char* getFileContents(const char* path) {
  char* buffer = 0;
  long len;

  FILE* f = fopen(path, "rb");

  if (f) {
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);

    buffer = calloc(len, len);

    if (buffer)
      fread(buffer, 1, len, f);

    fclose(f);

    return buffer;
  }

  printf("Error reading file %s\n", path);
  exit(2);
}