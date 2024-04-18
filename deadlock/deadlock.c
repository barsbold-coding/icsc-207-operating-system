#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {
  const uint8_t rn = 4, pn = 5; // resource number, process number
  uint8_t available[rn] = {1, 5, 2, 0};
  uint8_t allocation[pn][rn] = {
    {0, 0, 1, 2},
    {1, 0, 0, 0},
    {1, 3, 5, 4},
    {0, 6, 3, 2},
    {0, 0, 1, 4}
  };
  uint8_t max[pn][rn] = {
    {0, 0, 1, 2},
    {1, 7, 5, 0},
    {2, 3, 5, 6},
    {0, 6, 5, 2},
    {0, 6, 5, 6}
  };
  uint8_t need[pn][rn];
  for (int i = 0; i < pn; ++i) {
    printf("P%d: ", i);
    for (int j = 0; j < rn; ++j) {
      need[i][j] = max[i][j] - allocation[i][j];
      printf("%d ", need[i][j]);
    }
    printf("\n");
  }
  bool finish[pn];
  uint8_t ans[pn];
  int ind = 0;
  for (int i = 0; i < pn; ++i) {
    finish[i] = false;
  }
  for (int k = 0; k < 5; ++k) {
    for (int i = 0; i < pn; ++i) {
      if (!finish[i]) {
        bool flag = false;
        for (int j = 0; j < rn; ++j) {
          if (need[i][j] > available[j]) {
            flag = true;
            break;
          };
        }
        if (!flag) {
          ans[ind++] = i;
          for (int y = 0; y < rn; ++y)
            available[y] += allocation[i][y];

          finish[i] = true;
        }
      }
    }
  }

  bool flag = true;
  for (int i = 0; i < pn; ++i) {
    if (!finish[i]) {
      flag = false;
      printf("deallock detected\n");
    }
  }

  if (flag) {
    printf ("safe sequence\n");
    for (int i = 0; i < pn - 1; ++i)
      printf("P%d -> ", ans[i]);
    printf ("P%d\n", ans[pn - 1]);
  }

  return 0;
}
