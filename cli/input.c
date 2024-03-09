#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("missing arguments!\n");
    return EXIT_FAILURE;
  }
  FILE *fp = fopen(argv[1], "a");

  if (!fp) {
    printf("%s: no such file\n", argv[1]);
    return EXIT_FAILURE;
  }

  fprintf(fp, "%s", argv[2]);

  return EXIT_SUCCESS;
}
