#include <stdio.h>
#include <stdlib.h>

typedef union {
   int integer;
   double floating;
} number_t;

typedef struct {
   int length;
   number_t *body;
} array_t;

void array_t_new(array_t *ar, int length) {
   ar->length = length;
   ar->body = (number_t *)calloc(length, sizeof(number_t));
}

int main(void) {
   number_t u;
   // 联合体 u 一次只能存储一个值, 当为另一个成员赋值时, 前一个成员就被覆盖掉了.
   u.integer = 1;
   u.floating = 3.14;
   printf("%d %f\n", u.integer, u.floating);
   // u.integer 成员实际存储了 u.floating 成员的数据, 并且在打印时被强制解释成了整数
   printf("%d\n", *((int *)&u.floating));

   printf("************\n");

   array_t a;
   array_t_new(&a, 10);

   for (int i = 0; i < a.length; ++i) {
      a.body[i].floating = 1e9f / i + 1;
   }

   for (int i = 0; i < a.length; ++i) {
      printf("%p: %d, %f\n", &a.body[i], a.body[i].integer, a.body[i].floating);
   }

   return 0;
}
