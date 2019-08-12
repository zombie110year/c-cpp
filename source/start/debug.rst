####
调试
####

.. _`GDB 使用方法`:

GDB 使用方法
============

.. note:: Zombie110year

   现在有许多图形调试工具可以使用, 但是, 如果你有在控制台字符界面上 debug 的需求, 最好还是学一下 gdb 的用法.

调试的启动
----------

要通过 GDB 调试一个程序, 需要保证程序能够找到源码, 并且编译时开启 ``-g`` 选项以让可执行程序包含调试信息(源码文件位置以及行数等).

在开始调试之前, 先了解一些基础概念:

.. list-table::
   :header-columns: 1

   *  -  名词
      -  含义
   *  -  Launch(启动)
      -  Launch 是调试方式的一种, 它的含义是, 在调试开始的时候从头开始运行程序.
   *  -  Attach(附加)
      -  Attach 是另一种调试方式. 在一个程序正在运行的时候, Linux 系统会为它分配一个独有的进程号(PID), 通过 PID 和可执行文件,
         GDB 可以附加到正在运行的进程, 来进行调试.
   *  -  BreakPoint(断点)
      -  断点是在程序中对某一行代码的标注. 当程序运行到断点处将会暂停. 在这时, 可以使用 GDB 查看和修改内部状态.
   *  -  WatchPoint(观察点)
      -  观察点是一个在调试器进行一步调试后都会更新的表达式. 用来监控某个对象的修改.

下面, 以一个累加程序来说明调试步骤:

.. literalinclude:: _code/show.sum.c
   :linenos:

首先, 使用 ``-g`` 选项编译以携带调试信息:

.. code:: sh

   gcc -g show.sum.c

然后, 启动 gdb, (编译得到的可执行文件默认命名为 a.out):

.. code:: sh

   gdb ./a.out

随后, 就进入了 gdb 的命令环境, 这时候, 要调试的程序还没有运行:

.. sidebar:: gdb --tui

   另外, Linux 下的 gdb 提供了 ``--tui`` 选项, 以提供字符用户界面, 它将整个界面分成两份,
   上面显示源码, 下面是调试器指令窗口.

.. highlight:: text

::

   GNU gdb (GDB) 8.3
   Copyright (C) 2019 Free Software Foundation, Inc.
   License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
   Type "show copying" and "show warranty" for details.
   This GDB was configured as "x86_64-pc-linux-gnu".
   Type "show configuration" for configuration details.
   For bug reporting instructions, please see:
   <http://www.gnu.org/software/gdb/bugs/>.
   Find the GDB manual and other documentation resources online at:
       <http://www.gnu.org/software/gdb/documentation/>.

   For help, type "help".
   Type "apropos word" to search for commands related to "word"...
   Reading symbols from ./a.out...
   (gdb)

在这时, 可以先为文件打上断点, 以便后面的调试.
在很多情况下, 都需要反复地退出 gdb 修改源码, 然后再来调试.
gdb 可以读取当前工作目录下的 ``.gdbinit`` 文件,
在每次运行 gdb 先执行其中的指令.

在 gdb 命令环境中, 可以使用 ``list`` 指令列出源代码::

   (gdb) list

   1       #include <stdio.h>
   2       #include <stdlib.h>
   3       #include <time.h>
   4
   5       long long sum(const long long *array, size_t size) {
   6          long long _sum = 0;
   7          for (size_t i = 0; i < size; ++i) {
   8             _sum += *(array + i);
   9          }
   10         return _sum;

默认会列出 10 行. 在第二次 list 时, 会接着上一次的末尾列出.
``list`` 指令可以简写为 ``l``.

list 指令接受参数, 第一个参数是列出源码的基准位置, 可以有四种形式:

-  ``num``: 列出第 $num 行附近的代码(前后各半)
-  ``filename:num``: 列出文件 $filename 的第 $num 行附近的代码
-  ``function``: 列出函数 $function 附近的源代码.
-  ``filename:function``: 列出文件 $filename 中的名为 $function 的静态函数.

我们这次调试, 需要在第 8 行打上断点. 输入指令::

   (gdb) break 8
   Breakpoint 1 at 0x11aa: file show.sum.c, line 8.

或者使用 ``break`` 指令的简写 ``b``::

   (gdb) b 8

如果有很多断点要打, 就在 ``.gdbinit`` 文件中输入::

   b 8
   b 9
   b 10
   ...

在做好准备工作后, 就可以启动程序了, 使用 ``start`` 或 ``run`` 两种指令.
前者会在第一条代码处暂停, 等待之后的指令;
后者则是直接运行, 直到程序结束或遇到断点为止::

   (gdb) start
   Temporary breakpoint 2 at 0x11fa: file show.sum.c, line 14.
   Starting program: /home/zom/source/notes/c-cpp/source/start/_code/a.out

   Temporary breakpoint 2, main (argc=1, argv=0x7fffffffe368) at show.sum.c:14
   warning: Source file is more recent than executable.
   14         srand(time(NULL));

之后, 可以进行单步调试, 或者持续运行, 直到断点为止.
单步调试有两种模式, 一种叫 "单步

Core Dump
=========

Core Dump 是 Linux 系统在程序异常崩溃的时候为此程序的进程创建镜像文件的行为.
Core Dump 会将进程的内存状态, 例如调用栈, 寄存器状态, 内存管理系统,
和其他的操作系统以及处理器信息保存下来,
以帮助调试. 所保存的文件也被称为 coredump.
[#]_, [#]_.

最常见的 Core Dump 原因就是程序访问到了不属于进程的内存.
这种错误也被称作 *段错误(Segment Fault)*:

- 内存访问越界:

   1. 数组下标越界.
   2. 字符串未以 `\0` 结尾的情况下被读写.
   3. 使用 `strcpy` 等函数时输出缓冲区溢出, 最好使用 `strncpy` 等函数代替, 设定最大写入字符数.

- 非法指针:

   1. 读写 NULL 指针所指的地址.
   2. 错误的指针类型转换. 由于内存的对齐方式不一致而导致 bus error 触发 core dump

- 堆栈溢出等

Linux 系统与 Core Dump 相关的配置有:

1. ``ulimit`` 指令, 控制当前会话的 coredump 文件大小限制.
2. ``/etc/security/limits.conf`` 文件.
3. ``/proc/sys/kernel/core_pattern`` 配置 coredump 文件保存的机制.


对于 Debian 系的大部分发行版, 系统会自动在进程的 "当前工作目录" 产生一个名为 `core` 的文件.
而在 Arch 系的发行版, 则会使用 systemd-coredump 程序来进行 coredump 的产生与管理.

有些 Linux 发行版会将这个功能禁用, 可以在 `/etc/security/limits.conf` 这个配置文件中设置::

   # /etc/security/limits.conf
   #
   #Each line describes a limit for a user in the form:
   #
   #<domain>   <type>   <item>   <value>
      *          soft     core   unlimited

然后, 查看当前会话的 ``ulimit -c`` 的输出, 如果为 ``0``, 也不会产生 core dump.
这个选项用于查看或设定 core dump 文件大小限制, 单位是 KB.
可以设置为 `unlimited`, 从而产生不限大小的 core dump:

.. code-block:: sh

   ulimit -c unlimited

可以在 ``/proc/sys/kernel/core_pattern`` 文件中设置 core dump 的保存路径.
以 ``|`` 开头的行会被认为是要执行的命令, 所以 Arch 系的此文件中包含语句::

   |/usr/lib/systemd/systemd-coredump

这个文件不能通过编辑器修改, 需要使用重定向进行修改, 设置将 core dump 文件保存为:

.. code:: sh

   echo "%u.%e.%p.core" > /proc/sys/kernel/core_pattern

这样, 将会把产生的 core dump 文件保存在当前目录下,
文件名由进程的 UID, 可执行文件名, 进程的 PID 组成, 加上一个后缀 ``core`` 以示区分.

core dump 程序不会自动创建目录, 如果将它保存在一个固定的目录, 需要先创建目录:

.. code:: sh

   # echo "/tmp/coredump/%u.%e.%p.core" > /proc/sys/kernel/core_pattern
   mkdir /tmp/coredump

这样文件才能保存为 ``/tmp/coredump/%e.%u.%p.core``.

.. todo:: systemd-coredump

.. [#]  http://man7.org/linux/man-pages/man5/core.5.html
.. [#]  https://www.cnblogs.com/hazir/p/linxu_core_dump.html

Core Dump 调试方法
==================

用写 NULL 指针的例子来触发一次 Core Dump:

.. literalinclude:: _code/show.coredump.c
   :linenos:

当用 ``-g`` 选项编译后, 运行得到的程序即可获得 coredump 文件:

.. code::

   $ gdb a.out a.out.1000.21501.coredump

   Reading symbols from hello.out...
   [New LWP 21501]
   Core was generated by ./hello.out.
   Program terminated with signal SIGSEGV, Segmentation fault.
   #0  0x000056261d129143 in main () at hello.c:6
   6          *y = x;
   (gdb) where
   #0  0x000056261d129143 in main () at hello.c:6
   (gdb) info frame
   Stack level 0, frame at 0x7ffe3ad5ad00:
   rip = 0x56261d129143 in main (hello.c:6); saved rip = 0x7f75ebc35ce3
   source language c.
   Arglist at 0x7ffe3ad5acf0, args:
   Locals at 0x7ffe3ad5acf0, Previous frame's sp is 0x7ffe3ad5ad00
   Saved registers:
   rbp at 0x7ffe3ad5acf0, rip at 0x7ffe3ad5acf8
   (gdb) quit

在启动 gdb 时提供可执行文件(加载符号)和 coredump 文件, 则会将程序的状态恢复到 Core Dump 的前一刻,
此时就可以使用 GDB 进行调试了.

.. sidebar:: vscode 图形工具

   要使用 Visual Studio Code 的 C/C++ 调试工具对 Core Dump 进行调试,
   需要在 ``launch.json`` 中增加一项 "coreDumpPath".
