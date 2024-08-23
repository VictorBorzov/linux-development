#include <stdio.h>
#include <dirent.h>


void print_help(char** args) {
  printf("Usage: %s <directory>\n", args[0]);
}

char* get_message() {
  char* msg = "hello";
  return msg;
}

int main(int argsn, char** args) {
  char* s = get_message();
  puts(s);

 if (argsn != 2) {
    print_help(args);
    return 1;
  }

  char *dir_name = args[1];
  DIR *dir = opendir(dir_name);

  struct dirent *entry = readdir(dir);
  while(entry != NULL) {
    printf("%s\n", entry->d_name);
    entry = readdir(dir);
  }

  return 0;
}
