#include "array.h"
#include <stdio.h>

// array.c 中定义
index_t range(index_t t, index_t length);

void display(const array_t *array) {
   for(index_t i = 0; i < array->size; ++i) {
      printf("%lf", get(array, i));
      putchar(' ');
   }
   putchar('\n');
}

int main(void) {
   array_t *a = build(4, 1.0, 2.0, 3.0, 4.0);
   array_t *b = build(4, 5.0, 6.0, 7.0, 8.0);
   array_t *c = concat(a, b);
   array_t *d = copy(c);
   display(c);
   display(d);

   delete(d);
   delete(c);
   delete(b);
   delete(a);
   return 0;
}
