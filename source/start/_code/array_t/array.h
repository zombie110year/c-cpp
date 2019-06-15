#ifndef _ARRAY_T_HEAD
#define _ARRAY_T_HEAD
#include <stddef.h>
#include <stdarg.h>

typedef double number_t;
typedef long long int index_t;

struct _array_t {
   index_t size;
   number_t *body;
};

typedef struct _array_t array_t;

// 初始化数组
array_t *new(index_t size);
// 初始化数组并赋值
array_t *build(index_t size, ...);
// 删除数组
int delete(array_t *array);

// 引用一个元素
number_t *getElement(array_t *array, index_t index);
// 获取一个元素值
number_t get(const array_t *array, index_t index);
// 设置数组中某一项的值
int set(array_t *array, index_t index, number_t value);

// 复制两个等长的数组
array_t *copy(const array_t *src);
// 连接
array_t *concat(const array_t *src1, const array_t *src2);

#endif /* _ARRAY_T_HEAD */
