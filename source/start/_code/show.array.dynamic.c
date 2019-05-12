#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 在形式参数中, 指针与数组表示同样的意思
// 但是只能定义一维数组, 因为不知道数组每一维的长度
// 但是可以定义多级指针.
void add_one(int array[], int length) {
   for (int i = 0; i < length; ++i) {
      array[i]++;
   }
}

int main(void) {
   // 初始化随机数生成器
   srand(time(NULL));
   int length = rand() % 12; // 随机设置数组长度
   int *array = (int *)calloc(length, sizeof(int));
   for (int *i = array; i < (array + length); ++i) {
      *i = rand() % 1000;
   }
   printf("length: %d\n", length);
   for (int i = 0; i < length; ++i) {
      // 下标访问会被编译为指针访问, 对指针或数组都是如此
      printf("%d ", array[i]);
   }
   printf("\n");

   // 指针可作为函数实参
   add_one(array, length);

   for (int i = 0; i < length; ++i) {
      printf("%d ", array[i]);
   }

   printf("\n");
   return 0;
}
