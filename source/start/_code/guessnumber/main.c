#include "guessnumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double GOAL; // 与 guessnumber.c 中的 GOAL 同名
// 在链接后是同一实体
const int MAX_ANSWER = 1000;

int main(int argc, char const *argv[]) {
   int answer;
   // mainloop 返回的状态码, 用于判断是中断并返回还是因胜利而返回.
   status_t status;
   int goon = 1; // 是否继续游戏
   /**
    * 在 传入 NULL 的情况下, time 函数会直接将时间戳作为返回值返回,
    * 然后再作为参数传递给 srand 函数进行随机数生成器的初始化.
    */
   srand(time(NULL));
   while (goon) {
      // rand() 会随机返回一个整数,
      // 用模运算将其限制在 [0, 1000) 的范围中
      answer = rand() % MAX_ANSWER;

      status = mainloop(answer);
      switch (status) {
      case WIN: {
         char choice;
         printf("You Win! goal: %.0f\n", GOAL);
         printf("next round? [y/n]  ");
         fflush(stdout);
      ask_next_round:
         choice = getchar();
         if (choice == 'y') {
            goon = 1;
         } else if (choice == 'n') {
            goon = 0;
            printf("Total goal: %.0f\n", GOAL);
         } else {
            goto ask_next_round;
         }
         break;
      }
      case TERM: {
         goon = 0;
         break;
      }
      }
   }

   printf("Exit\n");
   return 0;
}
