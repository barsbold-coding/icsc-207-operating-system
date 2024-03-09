#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *find_prime_number(void *n) {
  int num = *((int *)n);
  if (num == 1) return NULL;

  for (int i = 2; i <= sqrt(num); i++) {
    if (num % i == 0) return NULL;
  }

  printf("%d\n", num);
  return NULL;
}

int main(void) {
  pthread_t thread_ids[100];
  int* nums = malloc(sizeof(int) * 100);

  for (int i = 1; i <= 100; ++i) {
    nums[i] = i;
    pthread_create(&thread_ids[i], NULL, find_prime_number, nums + i);
  }


  pthread_exit(NULL);

  free(nums);

  exit(0);
}
