#include <stdarg.h>
#include <stdio.h>

int _sum(int count, va_list args) {
   int sum = 0;
   for (int i = 0; i < count; ++i) {
      // 在 _sum 函数中, 仍然可以通过已初始化的 args 访问到 sum 函数帧的形参表位置.
      sum += va_arg(args, int);
   }
   return sum;
}

// 后面的可变参数都是 int 类型的
int sum(int count, ...) {
   va_list args;
   // 记录 sum 函数帧中的形参位置
   va_start(args, count);
   // 将 args 传递给另一个函数
   int res = _sum(count, args);
   va_end(args);
   return res;
}

int main(void) {
   printf("%d\n", sum(3, 1, 2, 3));
   return 0;
}
