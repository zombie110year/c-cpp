CC = clang
CFLAGS = -g -Wall
INCLUDE =
LIB =
# 有可能你的包管理器没有将 cunit 安装在
# /usr/include 和 /usr/lib 目录下,
# 那么, 需要手动设置 INCLUDE 和 LIB 变量
# 一些包管理器将安装的第三方库存储在 /usr/local 目录下:
#
# INCLUDE += -I/usr/local/include
# LIB += -L/usr/local/lib

.PHONY: test clean

test: test.out
	./test.out

clean: array.o test.out
	rm $^

array.o: array.c array.h
	$(CC) $(CFLAGS) -c $<

test.o: test.c
	$(CC) $(CFLAGS) -c $<

test.out: test.o array.o
	$(CC) $(CFLAGS) $(INCLUDE) $(LIB) \
	-o $@ $^
