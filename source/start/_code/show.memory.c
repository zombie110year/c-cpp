/**
 *  这个程序没有实际意义, 只是展示变量的存储类型而已.
 */
#include <stdio.h>
#include <stdlib.h>

// 在全局作用域中, 关键字 static 可省略
const int in_rodata = 0; // .rodata
int in_rwdata = 1;       // .rwdata
int in_bss;            // .bss

void increase(void);

int main(void) {
   int a = 1; // a 位于 stack, 而字面量 1 将被保存在 .rodata
   int *b;    // b 位于 stack
   char *str = "你好";
   // 字面量 "你好" 位于 .rodata 段
   // 指针 str 位于 stack
   b = malloc(4); // 字面量将保存在 .rodata
   // 通过 malloc 分配的数据位于 heap
   // 指针 b 位于 stack
   for (int i = 0; i < 10; ++i) {
      increase();
   }
}

void increase(void) {
   static int counter = 0; // .rwdata
   static int goal;        // .bss
   printf("%d\n", counter++);
}
