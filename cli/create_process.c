#include <stdio.h>
#include <stdlib.h>
#include <sys/syslimits.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  char cwd[PATH_MAX];
  if (argc <= 2) {
    printf("argument is missing");
    return EXIT_FAILURE;
  }

  pid_t child_pid = fork();

  if (child_pid < 0) {
    perror("fork failed");
  } else if (child_pid == 0) {
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    char *args[] = { cwd };
    printf("this is invoked with child process (PID: %d)\n", getpid());
    execlp(argv[1], NULL);

  } else {
    int status;
    wait(&status);
    printf("Parent process (PID: %d): My child process terminated.\n", getpid());
  }

  return EXIT_SUCCESS;
}
