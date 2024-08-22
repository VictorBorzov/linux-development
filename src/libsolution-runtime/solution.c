#include <stdio.h>
#include <string.h>

int stringStat(const char *string, size_t multiplier, int *count) {
  (*count)++;
  return strlen(string) * multiplier;
}


int main(int argc, char** args) {
  if (argc != 4) {
    puts("Expected 3 arguments");
    return 1;
  }
  char* libName = args[1];
  char* funcName = args[2];
  int param = (int)args[3];
  printf("libname: %s\nfunc: %s\nparam: %i\n", libName, funcName, param);
}
