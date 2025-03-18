#define _GNU_SOURCE

@load "fork"

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

#define array_length(arr) (sizeof(arr) == 0 ? 0 : sizeof(arr)/sizeof(*arr))

void print_help(char** args) {
  fprintf(stderr, "Usage: %s [SUBCOMMAND] [OPTIONS] <directory>\n", args[0]);
  fprintf(stderr, "OPTIONS:\n");
  fprintf(stderr, "    cat <file>       print file content\n");
  fprintf(stderr, "    ls <directory>   list directory\n");
}

int cat(int argc, char** args) {
  if (argc != 3) {
    print_help(args);
    return 1;
  }

  char buf[100];
  size_t sz = 0;

  int fd = open(args[2], O_RDONLY|O_PATH);
  perror("fd");
  printf("fd = %d\n", fd);
  sz = read(fd, buf, 100);
  printf("sz = %ld\n", sz);
  return 0;
}

int ls(int argc, char** args) {
  if (argc != 3) {
    print_help(args);
    return 1;
  }

  char *dir_name = args[2];
  DIR *dir = opendir(dir_name);

  struct dirent *entry = readdir(dir);
  while(entry != NULL) {
    printf("%s\n", entry->d_name);
    entry = readdir(dir);
  }

  closedir(dir);
  return 0;
}

char* to_lower(char* s) {
  for (int i = 0; i < strlen(s); ++i) {
    s[i] = tolower(s[i]);
  }
  return s;
}

int main(int argc, char** args) {
  if (argc < 2) {
    print_help(args);
    return 1;
  }

  char* subcommand = args[1];
  if (strcoll(to_lower(subcommand), "cat") == 0) {
    return cat(argc, args);
  } else if (strcoll(to_lower(subcommand), "ls") == 0) {
    return ls(argc, args);
  } else {
    print_help(args);
    return 1;
  }
}
