#include <stdio.h>

// 位运算交换两值
void swap(int *a, int *b) {
   *a ^= *b;
   *b ^= *a;
   *a ^= *b;
}

void swapf(double *a, double *b) {
   long *x = (long *)a;
   long *y = (long *)b;
   // 位运算不在乎类型.
   // 但浮点数不能进行位运算,
   // 这里通过修改指针类型将浮点数的二进制数据当作整数来进行位运算.
   // 最终还是按照浮点数类型进行解读.
   *x ^= *y;
   *y ^= *x;
   *x ^= *y;
}

typedef void(* swapf_func_t)(double*, double *);

int main(void) {
   int a = 1;
   int b = 2;
   double x = 3.3;
   double y = 4.4;
   // 声明函数指针 fp, 可指向 swap 这样的返回类型为 void, 参数为 int*, int* 的函数.
   void (*fp)(int *, int *);
   fp = &swap;
   // fp = swap // 也可, swap 标识符本身就代表该函数对应的代码块的首地址

   // 对函数指针解引用, 再传入参数表以调用
   (*fp)(&a, &b);
   printf("%d %d\n", a, b);

   // swapf_func_t 可以用于声明 void(*)(double*, double*) 类型的函数指针
   swapf_func_t fpf = swapf;
   (*fpf)(&x, &y);
   printf("%f %f\n", x, y);
   return 0;
}
