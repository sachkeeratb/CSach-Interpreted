#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/io.h"

char* getFileContents(const char* path) {
  const char* givenExt = strrchr(path, '.');

  if (strcmp(givenExt, ".csach") != 0) {
    printf("File %s does not have the correct extention of \".csach\"\n", path);
    exit(2);
  }

  char* buffer = 0;
  long len;

  FILE* f = fopen(path, "rb");

  if (!f) {
    printf("Error reading file %s\n", path);
    exit(2);
  }

  fseek(f, 0, SEEK_END);
  len = ftell(f);
  fseek(f, 0, SEEK_SET);

  buffer = calloc(len, len);

  if (!buffer) {
    printf("Error reading file %s\n", path);
    exit(2);
  }

  fread(buffer, 1, len, f);

  fclose(f);

  return buffer;  
}