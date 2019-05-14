###########
编译 C 程序
###########

在开始学习 C 语言的语法之前, 先来了解如何将源代码编译成可执行的程序.

如何编写一个 C 程序
===================

一个 C 程序通常由 C 代码和 C 标准库提供的功能组成.
C 标准库提供的功能需要通过在自己编写的 C 代码中包含对应的头文件才能使用.

编写 C 程序时, 一般在 ``.c`` 后缀的文件中编写程序的主要逻辑,
在 ``.h`` 后缀的文件中编写此程序公开的类型、变量、函数等.

``.c`` 文件一般称作 "源代码", 而 ``.h`` 文件一般称作 "头文件".

先准备一个可编译的 C 代码源文件:

.. _`hello.c`:

.. literalinclude:: _code/hello.c
   :language: c
   :caption: hello.c
   :linenos:

第一行的 ``#include <stdio.h>`` 是一个 *预处理* 指令,
作用就是包含 C 标准库头文件 ``stdio.h`` 中的内容.
在这个文件中, 提供了 C 标准库与输入输出有关的函数声明与类型定义.

通过引入头文件中的声明, 才能在编译过程中正确地链接到 C 标准库中的符号.

之后的内容就是编辑的 C 代码, C 代码从一个 ``main`` 函数开始,
这被称为 `程序入口`_.

编译过程
========

对于传统的编译过程, 如使用 clang 进行编译, 我们会使用这样的命令行:

.. code-block:: sh

   clang -Wall -g -o hello hello.c

-  ``clang`` 要执行的程序名称, clang 是 Clang 编译器用来编译 C 语言的可执行程序.
-  ``-Wall`` clang 程序的一个参数, 意思是报告所有警告.
   警告是指在程序中那些不算错误, 但是可能导致程序运行不正常的代码.
-  ``-g`` clang 程序的一个参数, 意思是保留调试信息. 只有保留调试信息, 才能在调试时找到程序片段对应的源代码.
-  ``-o hello`` 设置输出文件的路径, 默认为 ``a.out``
-  ``hello.c`` 剩下的参数表示输入的源代码路径.

在执行上述指令时, 编译器做了这些事:

1. **预处理**: 首先将源代码 "喂" 给预处理器.
   预处理将会展开文件中的预处理指令与宏.
   C/C++ 中使用的预处理指令都是以 ``#`` 开头的.
   例如 :ref:`hello.c` 中第一行的 ``#include``.
   这个指令会将 ``/usr/include/stdio.h`` 中的内容包含到当前文件中来.
   并且 stdio.h 中的预处理指令与宏也会被展开.

现在, 我们得到了预处理后的源代码文件. 我们可以看到,
在文件开头的 ``#include <stdio.h>`` 已经变成了长达 700 多行的代码.
而在文件的尾部, 我们刚定义的 ``main`` 函数还是保持了原样没有改变.

.. literalinclude:: _code/hello.i
   :language: c
   :caption: hello.i
   :linenos:
   :lines: 1-10,729-

.. note:: 中间的 700 多行代码被剪掉了

2. **编译**: 在得到预处理后的代码之后, 这段代码就将喂给编译器进行处理.
   编译器会将代码编译成 "汇编" 代码. 关于汇编代码, 我们需要知道的是:

   -  汇编代码与 CPU 执行的机器码一一对应
   -  不同的 CPU 只能执行其指令集所实现的代码

   因此, 也是整个编译过程最重要的一步. 也是以这一步来命名了整个编译过程.

.. literalinclude:: _code/hello.s
   :language: asm
   :caption: hello.s
   :linenos:

3. **汇编**: 得到汇编代码之后, 就直接一步一步地将它翻译成机器码就好了.
   这一步之后, 得到了二进制目标代码 ``hello.o`` (有删减, 只保留了消息较密集的部分).

.. literalinclude:: _code/hello.o.txt
   :language: hexdump
   :caption: hello.o(有删减)
   :lines: 1-15,34-43
   :emphasize-lines: 8-9

使用 Linux 程序 xxd 将整个文件转换成了可读性更好的形式,
整个文件被分为三栏::

   <地址>:   <各地址上的字节>                         <字节对应的字符>
   00000000: 7f45 4c46 0201 0100 0000 0000 0000 0000  .ELF............

``.`` 号表示这个字节没有对应的可显示字符.
还可以发现, 我们要打印的字符串 "Hello World!" 也出现在了目标代码里.

4. **链接**: 得到了二进制目标代码, 但是这个程序仍然不可执行.
   并且, 还注意到在源代码中使用的 :c:func:`printf` 还仅仅是声明,
   可没有定义对应的实现呢(在 hello.o 中, 编译器留下了 ``llvm_addrsig.printf`` 记号).
   因此, 还需要将中间代码与 C 标准库相链接, 把 printf 的代码与 printf 这个符号相关联.

.. literalinclude:: _code/hello.txt
   :language: hexdump
   :caption: hello(有删减)
   :lines: 1,43-46

.. 觉得太长, 后面的行就不要显示了 63-71,257-289,513-529,771-777,873-921

链接完成了之后, 终于得到可执行程序 ``hello`` 了.
现在, 让我们在终端运行它一下:

.. code:: bash

   ./hello

.. code::

   Hello World!

另外, clang 还会生成一个 ``hello.bc`` 文件, 那是 LLVM 的中间码.
它的生成是 LLVM 调用后端编译之前的一步.

.. list-table::

   *  -  编译过程
      -  Clang 编译过程
   *  -  .. graphviz:: ../_static/graphviz/intro.compile.gv
      -  .. graphviz:: ../_static/graphviz/intro.compile.clang.gv

程序入口
========

一个程序必须要有一个开始执行的位置, 对于 C 程序来说, 这个入口就是函数 ``main``,
所以你能在所有 **编译得到可执行文件的源代码** 中看到一个名为 ``main`` 的函数.

为什么要强调是 **得到可执行文件的源代码** ?

还记得在 `编译过程`_ 中提到的最后一个步骤: *链接* 吗,
在这个步骤中, 链接的目标 -- libc 就是一个链接库文件,
在链接库文件中, 可以不包含 ``main`` 函数.

链接库中存储了编译后的程序代码以及它们的符号,
可以链接到其他函数中使用. 具体的用法见 :doc:`library`.

继续说主函数, 在 :ref:`hello.c` 中, 主函数的 *形参(Parameter)* 表为 ``int argc, char *argv[]``:

.. literalinclude:: _code/hello.c
   :language: c
   :lines: 3

这是为了能够从命令行接收参数. ``argc`` 是所传入参数的数目,
``argv`` 则是存储了指向每一个参数的首地址的指针.
参数的类型都是字符串.
你可以使用 C 标准库提供的 :c:func:`atoi`, :c:func:`atof` 来将字符串解析为对应的整数或浮点数.
这两个函数的声明包含在头文件 ``stdlib.h`` 中.

当从终端调用程序时, 可以这样向程序传递参数:

.. code-block:: sh

   ./hello arg1 arg2 arg3

如此, 则 ``argc`` 的值将会为 4, ``argv`` 则是一个指向四个字符串的指针数组:

.. code::

   argv[0] -> "./hello"
   argv[1] -> "arg1"
   argv[2] -> "arg2"
   argv[3] -> "arg3"

``argc`` 和 ``argv`` 都是惯用名, 并非必须这么做, 你也可以这么命名::

   int main(int argument_counts, char *argument_variables[]) {

练习
====

1. 在自己的机器上编译并运行 hello.c 程序::

   #include <stdio.h>

   int main(int argc, char *argv[]) {
      printf("Hello World!\n");
      return 0;
   }


2. 去掉 :ref:`hello.c` 中的 ``#include <stdio.h>``, 看看编译器报错是什么.
3. 用 ``extern int printf(const char *restrict, ...);``
   代替 ``#include <stdio.h>``, 看看能否重新编译. 思考头文件的作用::

   extern int printf(const char *restrict, ...);

   int main(int argc, char *argv[]) {
      printf("Hello World!\n");
      return 0;
   }

.. todo:: 练习的参考答案

   1. 使用命令行 ``clang hello.c`` 生成的 ``a.out`` 就是可执行文件.
   2. 由链接器报出 undefined label 之类的错误
   3. 此代码应当能成功编译, 并正常运行. 头文件就是提供了相关的函数以及变量声明,
      在链接步骤后, 这些符号将指向标准库中的代码.
