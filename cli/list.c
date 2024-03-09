#include <stdint.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_off_t.h>
#include <sys/stat.h>

#define STR_MAX_LEN 20

char* resolve_d_type(uint8_t d_type) {
  switch (d_type) {
    case DT_DIR:
      return "dir";
    case DT_REG:
      return "fil";
    default:
      return "unk";
  }
}

char* format_str(char* str, uint8_t len) {
  char *destination = malloc(len + 1);

  uint8_t space_len = len - strlen(str);

  snprintf(destination, STR_MAX_LEN, "%s%*c", str, space_len, ' ');

  return destination;
}

char* format_size(off_t size) {
  char *destination = malloc(10);
  double formatted = (double)size / 1000;
  sprintf(destination, "%.2lfMB", formatted);
  return destination;
}

void print_dir_list(char* path) {
  DIR *dirp = opendir(path);
  struct dirent *dp;

  printf(
    "%s %s %s\n\n",
    format_str("name", STR_MAX_LEN),
    format_str("type", 5),
    "size"
  );

  while (dirp) {
    if ((dp = readdir(dirp)) != NULL) {
      struct stat statbuf;
        if (stat(dp->d_name, &statbuf) == -1) {
          perror("stat");
          continue;
        }
      printf(
        "%s %s %s\n",
        format_str(dp->d_name, STR_MAX_LEN),
        format_str(resolve_d_type(dp->d_type), 5),
        format_size(statbuf.st_size)
      );
    } else {
      closedir(dirp);
      return;
    }
  }
}


int main(int argc, char** argv) {
  if (argc == 1) {
    print_dir_list(".");
    return EXIT_SUCCESS;
  }

  print_dir_list(argv[1]);

  return EXIT_SUCCESS;
}
