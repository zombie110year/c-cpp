#include <stdio.h>

int new (int *, int, int);
const int add(int, int);

int main(void) {
   int result;

   new(&result, 2, 3);
   printf("%d\n", result);

   result = add(5, 6);
   printf("%d\n", result);
   result += 12;
   printf("%d\n", result);

   return 0;
}

int new (int *const sum, int a, int b) {
   // sum 不会被指向其他位置
   *sum = a + b;
   return 0;
}

const int add(int a, int b) {
   // 返回值是一个常量
   return a + b;
}
