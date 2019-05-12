/**
 * 探究 sizeof 运算符是如何处理数组的
 */
#include <stdio.h>

int main(void) {
   unsigned int array[3] = {1, 2, 3};
   size_t *array_p = (size_t *) array;
   printf("array's address: %p\n", array);
   printf("array's previous value: %lu\n", *(array_p - 1));
   printf("array's length: %lu\n", sizeof array);
   return 0;
}
