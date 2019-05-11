#include <stdio.h>
int array[4][3] = {
    {0, 1, 2},   // 0
    {3, 4, 5},   // 1
    {6, 7, 8},   // 2
    {9, 10, 11}, // 3
};

int main(void) {
   for(int i = 0; i < 4; ++i) {
      for(int j = 0; j < 3; ++j) {
         printf("%d ", array[i][j]);
      }
      printf("\n");
   }
   return 0;
}
