#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("argument is missing!");
    return EXIT_FAILURE;
  }
  return remove(argv[1]);
}
