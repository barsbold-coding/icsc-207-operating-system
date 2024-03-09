#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/***
 * https://unix.stackexchange.com/questions/141313/chdirdirectory-doesnt-change-directory-after-exiting-to-shell
 ***/

int main(int argc, char** argv) {
  if (argc <= 1) {
    printf("Please specify a directory.\n");
    return EXIT_FAILURE;
  }

  int result = chdir(argv[1]);
  if (result != 0) {
    printf("Error changing directory: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  printf("Directory changed successfully.\n");
  return EXIT_SUCCESS;
}
