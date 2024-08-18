#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <dlfcn.h>

void (*hello_message)(const char*);

bool init_library() {
  void* handle = dlopen("./libHello.so", RTLD_LAZY);
  if (NULL == handle) {
    return false;
  }

  hello_message = (void (*)(const char*))dlsym(handle, "hello_message");
  if (NULL == hello_message) {
    return false;
  }

  return true;
}

int main() {
  if (init_library()) {
    hello_message("urmom");
  } else {
    printf("Library was not loaded\n");
  }

  return 0;
}
