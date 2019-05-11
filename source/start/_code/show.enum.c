#include <stdio.h>

enum status {
   PASS,               // 0  成功
   UNKOWN_ERROR,       // 1  未知错误
   MEMORY_ALLOC_ERROR, // 2  内存分配错误
   OVERRANGE_ERROR     // 3 访问越界错误
};

typedef enum {
   Monday = 1, // 1
   Tuesday,    // 2
   Wednesday,  // 3
   Thursday,
   Friday,
   Saturday,
   Sunday = 0
} week_t;

int main(void) {

   for(enum status i = PASS; i <= OVERRANGE_ERROR; ++i) {
      printf("%d ", i);
   }
   printf("\n");
   for(week_t i = Sunday; i <= Saturday; ++i) {
      printf("%d ", i);
   }
   printf("\n");
   printf("%d\n", Monday == UNKOWN_ERROR);
   return 0;
}
