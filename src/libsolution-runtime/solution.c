#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <dlfcn.h>

int (*lib_call)(int);

bool init_library(char* lib_name, char* func_name, int param) {
  void* handle = dlopen(lib_name, RTLD_LAZY);
  if (NULL == handle) {
    printf("Could not load handle %s\n", lib_name);
    return false;
  }

  lib_call = (int (*)(int))dlsym(handle, func_name);
  if (NULL == lib_call) {
    return false;
  }

  int result = lib_call(param);
  printf("%i\n", result);

  return true;
}

int main(int argc, char** args) {
  if (argc != 4) {
    puts("Expected 3 arguments");
    return 1;
  }
  if (init_library(args[1], args[2], atoi(args[3]))) {
    return 0;
  }

  puts("Library not loaded");
  return 1;
}
