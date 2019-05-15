#ifndef GUESSNUMBER_H
#define GUESSNUMBER_H

typedef enum {
   WIN, // 胜利
   TERM, // 中断
} status_t;

// 公开的函数
status_t mainloop(const int answer);
// 分数
extern double GOAL;
// 猜测数的最大值
extern const int MAX_ANSWER;

#endif /* GUESSNUMBER_H */
