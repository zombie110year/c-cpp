#include <stdio.h>

// 判断是否为奇数
inline int is_even(int);

int is_even(int x) {
   return (x & 1) != 0;
}

int main(void) {
   int a[3] = {1, 2, 3};
   for(int i = 0; i < 3; ++i) {
      if (is_even(a[i])) {
         printf("%d 是奇数\n", a[i]);
      }
   }
   return 0;
}
