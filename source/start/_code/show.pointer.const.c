#include <stdio.h>

int main(void) {
   int array[] = {1, 2, 3};
   // 不能修改值
   const int *p1 = array;
   // 不能修改指向
   int *const p2 = array + 1;
   // 两者皆有
   const int *const p3 = array + 2;

   printf("array: %p\n", array);
   printf("p1: %p\n", p1);
   printf("p2: %p\n", p2);

   p1 = array + 1;
   *p2 = 22;

   printf("p1: %p\n", p1);
   printf("p2, v(p2): %p, %d\n",p2, array[1]);
   // 取消以下注释则编译报错
   // *p1 = 11;
   // p2 = array;

   return 0;
}
