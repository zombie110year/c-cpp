.. _`C 语言标准库`:

############
C 语言标准库
############

对于 Linux 系统, 标准库头文件处于目录
``/usr/include`` 之下.
对应的链接库则位于 ``/lib/x86_64-linux-gnu/libc.so.6``.

实际上这是个符号链接, 指向了 ``/lib/x86_64-linux-gnu/libc-2.27.so``.
(或者其他版本)

Linux 下的 C 标准库由 GNU 实现, 被称作 "glibc".
由于 Linux 操作系统对 libc 由很强的依赖, 所以不建议更新到最新版本.

libc 一般都可执行以显示版本信息

.. code:: text

   $ /lib/x86_64-linux-gnu/libc.so.6

   GNU C Library (Debian GLIBC 2.27-3) stable release version 2.27.
   Copyright (C) 2018 Free Software Foundation, Inc.
   This is free software; see the source for copying conditions.
   There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
   PARTICULAR PURPOSE.
   Compiled by GNU CC version 7.3.0.
   libc ABIs: UNIQUE IFUNC
   For bug reporting instructions, please see:
   <http://www.debian.org/Bugs/>.

从路径上可以看出不同的 CPU 架构会影响系统存放库文件的路径.
``x86_64-linux-gnu`` 这个命名就表示, CPU 架构为 ``x86_64``, linux 操作系统, GNU 工具链.

标准库根据用途不同分成了 15 个不同的头文件.
但在编译时都是链接同一个二进制库文件.
链接指令是默认且隐藏的, 也可以在链接时显式添加选项 ``-lc`` 以链接到 libc.

assert.h
   提供一个宏, 验证一个表达式的布尔值, 当值为假时中断并输出诊断信息.

ctype.h
   提供了检查变量数值类型的函数.

errno.h
   提供整数变量 ``errno``, 此变量由系统维护,
   其值对应了不同的错误类型, 可用指令 ``man errno`` 查看

float.h
   提供了当前平台关于浮点数标准的常量. 只提供信息, 不提供功能.

limits.h
   提供了当前平台关于各类型数值极限的常量. 只提供信息, 不提供功能.

locale.h
   与本地化相关的数据结构与函数. 可用于设定日期格式, 货币符号等等.

math.h
   一系列数学计算函数. 参数与返回值都是 double 类型.

setjmp.h
   强大的跳转功能. 比 goto 语句更强大也更难用. 不推荐使用.

signal.h
   处理系统信号.

stdarg.h
   提供了一个变长参数列表类型用于函数定义.

stddef.h
   定义的标准扩展类型与宏. 其他头文件大多包含了此头文件.

stdio.h
   与输入输出相关的类型, 函数与宏.

stdlib.h
   通用工具. 与随机数相关的函数与宏也在此头文件中.

string.h
   处理字符串(字符数组).

time.h
   操作日期与时间.


.. toctree::
   :maxdepth: 2

   assert
   math
   stdarg
   stddef
   stdio
   stdlib
   string
   time
