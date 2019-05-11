#include <stdio.h>

// 静态变量, 全局作用域中 static 可省略
static int counter = 0;
static int timer = 0;

// 静态变量可在所有函数中被访问
void counterAdd(void) { counter++; }

// 函数声明
void showTimer(void);

int main(void) {
   // 自动变量, auto 可省略
   auto int this = 0;
   timer = 1;
   // 将循环控制变量声明为寄存器存储类型
   for (register int i = 0; i < 10000; ++i) {
      counterAdd();
      this ++;
   }
   showTimer();
   printf("counter: %d\n", counter);
   printf("this: %d\n", this);
}

// 在 main 前方声明此函数, 以便 main 函数调用.
void showTimer(void) { printf("timer: %d\n", timer); }
