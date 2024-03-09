#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("arguments are missing!\n");
    return EXIT_FAILURE;
  }

  return rename(argv[1], argv[2]);
}
