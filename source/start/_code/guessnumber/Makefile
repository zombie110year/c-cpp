CC = clang
# -lm 表示链接 libm (math.h)
CFLAGS = -g -Wall -lm
source := $(wildcard *.c)
target := guessnumber

$(target): $(source)
	$(CC) $(CFLAGS) -o $@ $^
