#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("missing argument!");
    return EXIT_FAILURE;
  }

  FILE* fp = fopen(argv[1], "r");

  if (fp != NULL) {
    fclose(fp);
    printf("%s is existing in current directory\n", argv[1]);
    printf("Do you want to overwrite the file? [yes/No]");
    char overwrite;
    scanf("%c", &overwrite);
    if (overwrite == 'y') {
      printf("creating %s\n", argv[1]);
      fp = fopen(argv[1], "w+");
    } else {
      return EXIT_FAILURE;
    }
  } else {
    fclose(fp);
    printf("creating %s\n", argv[1]);
    fp = fopen(argv[1], "w+");
  }

  return EXIT_SUCCESS;
}
