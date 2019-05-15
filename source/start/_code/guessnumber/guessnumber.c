#include "guessnumber.h"
#include <math.h> // 使用 math.h, 需要链接 libm
#include <stdio.h>

// 只在此文件中声明的函数, 在 main.c 中不可见
// 通过猜测次数计算分数
void addGoal(const int count);
// 只在此文件中声明的变量, 在 main.c 中不可见
// 每赢一局游戏所增加的基准分数
const double goal_d = 10.0;

status_t mainloop(const int answer) {
   int guess;     // 用户猜测的数
   int count = 0; // 猜测次数
   while (!feof(stdin)) {
      printf("guess > "); // 打印提示符
      // stdout 默认是行缓冲的, 而上面的 printf 没有换行符,
      // 因此不会直接输出
      fflush(stdout); // 刷新输出缓冲区
      scanf("%d", &guess);
      count++;
      if (guess == answer) {
         addGoal(count);
         return WIN; // 胜利退出
      } else if (guess < answer) {
         printf("%d < answer\n", guess);
      } else {
         printf("%d > answer\n", guess);
      }
   }
   return TERM; // 中断退出
}

void addGoal(const int count) {
   // 二分查找步骤数的期望值
   // 四舍五入
   int expected = (int)(log2((int)MAX_ANSWER) + 0.5);
   double addition = (double)(count - expected);
   if (addition <= 0) {
      GOAL += 10.0;
   } else {
      GOAL += 10.0 / log(addition + 1);
   }
}
