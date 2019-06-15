#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long sum(const long long *array, size_t size) {
   long long _sum = 0;
   for (size_t i = 0; i < size; ++i) {
      _sum += *(array + i);
   }
   return _sum;
}

int main(int argc, char const *argv[]) {
   srand(time(NULL));
   size_t size = rand() % 10;
   long long *array = (long long *)calloc(size, sizeof(long long));
   for (size_t i = 0; i < size; ++i) {
      *(array + i) = i;
   }

   printf("%lld\n", sum(array, size));

   return 0;
}
