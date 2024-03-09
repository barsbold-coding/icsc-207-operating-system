#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int    m1[2][3];
int    m2[3][2];
int m_res[2][2];

struct vector {
  unsigned short x;
  unsigned short y;
};

void * multiply(void *arg) {
  struct vector *cell = (struct vector*)arg;

  int res = 0;

  for (int i = 0; i < 3; i++) {
    res += m1[cell->x][i] * m2[i][cell->y];
  }

  m_res[cell->x][cell->y] = res;

  return NULL;
}

int main(void) {
  arc4random_buf(m1, sizeof m1);
  arc4random_buf(m2, sizeof m2);

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) {
      m1[i][j] = m1[i][j] % 100;
      m2[j][i] = m2[j][i] % 100;
    }

  printf("First matrix:\n");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d ", m1[i][j]);
    }
    printf("\n");
  }
  printf("Second matrix:\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      printf("%d ", m2[i][j]);
    }
    printf("\n");
  }

  pthread_t t_ids[4];
  struct vector cells[4];

  int k = 0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) {
      cells[k].x = i;
      cells[k].y = j;
      pthread_create(&t_ids[k], NULL, multiply, &cells[k]);
      pthread_join(t_ids[k], NULL);
      k++;
    }

  printf("Product matrix:\n");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      printf("%d ", m_res[i][j]);
    }
    printf("\n");
  }

  return 0;
}
