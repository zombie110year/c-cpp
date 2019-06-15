#include "array.h"
#include <stdlib.h>

// 将索引值化归到 range 范围中
index_t range(index_t t, index_t length) {
   return t % length;
}

array_t *new (index_t size) {
   array_t *array = (array_t *)malloc(sizeof(array_t));
   array->body = (number_t *)calloc(size, sizeof(number_t));
   array->size = size;
   return array;
}

array_t *build(index_t size, ...) {
   array_t *array = new (size);
   va_list _args;
   va_start(_args, size);

   for (index_t i = 0; i < size; ++i) {
      *getElement(array, i) = va_arg(_args, number_t);
   }
   va_end(_args);
   return array;
}

int delete (array_t *array) {
   free(array->body);
   free(array);
   return 0;
}

number_t *getElement(array_t *array, index_t index) {
   // 可从
   // 返回指针
   return (array->body + index);
}

number_t get(const array_t *array, index_t index) {
   // 对 getElement 返回的指针解引用, 返回数值
   return *getElement((array_t *)array, index);
}

int set(array_t *array, index_t index, number_t value) {
   *getElement(array, index) = value;
   return 0;
}

array_t *copy(const array_t *src) {
   array_t *dest = new(src->size);
   for(index_t i = 0; i < src->size; ++i) {
      set(dest, i, get(src, i));
   }
   return dest;
}

array_t* concat(const array_t *src1, const array_t *src2) {
   array_t *dest = new(src1->size + src2->size);
   for(index_t i = 0; i < src1->size; ++i) {
      set(dest, i, get(src1, i));
   }
   for(index_t i = 0; i < src2->size; ++i) {
      set(dest, src1->size + i, get(src2, i));
   }
   return dest;
}
