#include <stdio.h>

int main(void) {
  printf("char: %lu\n", sizeof(char));
  printf("short int: %lu\n", sizeof(short int));
  printf("int: %lu\n", sizeof(int));
  printf("long int: %lu\n", sizeof(long int));
  printf("long long int: %lu\n", sizeof(long long int));
  printf("float: %lu\n", sizeof(float));
  printf("double: %lu\n", sizeof(double));
  printf("long double: %lu\n", sizeof(long double));
  printf("unsigned short int: %lu\n", sizeof(unsigned short int));
  printf("unsigned int: %lu\n", sizeof(unsigned int));
  printf("unsigned long int: %lu\n", sizeof(unsigned long int));
  printf("unsigned long long int: %lu\n", sizeof(unsigned long long int));
}
