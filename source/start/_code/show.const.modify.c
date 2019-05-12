#include <stdio.h>

/**
 * 不同的编译器具有不同的表现:
 *
 * -  gcc: a 的值被修改了
 * -  clang: a 的值未被修改, 但可以通过 *y 访问到修改后的值
 *    但奇怪的是, y 和 &a 是相同的地址.
 */

int main(void) {
   const int a = 1;
   int *y =(int *) &a;
   printf("%p: %d, %p: %d\n", &a, a, y, *y);
   *y = 2;
   printf("%p: %d, %p: %d\n", &a, a, y, *y);
   printf("%d\n", a + *y);
   return 0;
}
