####
前言
####

本书主要内容
============

本书的内容组织首先从 :ref:`C 语言入门` 开始, 在此卷中, 讲解 C 语言的语法,
编译程序的步骤, 以及对可执行程序和内存结构的简单科普. 并且学习 :ref:`C 语言标准库` 的使用.

然后, 进入两个分支, 一个分支是进入 C++ 的学习, 从 :ref:`从 C 扩展到 C++` 开始, 然后按照:

1. :ref:`在 C++ 中摆脱 C`
#. :ref:`C++ 标准库与标准模板库`
#. :ref:`C++ 新特性`
#. :ref:`C++ 编程模式`

的顺序学习 C++ 语言.

或者通过 C 语言了解计算机、 操作系统以及简单的数据结构与算法.

1. :ref:`C 编程模式`
#. :ref:`通过 C 语言认识计算机`
#. :ref:`C 数据结构与算法`

C 与 C++ 有很多重叠的部分, 例如

-  :ref:`C/C++ 内联汇编`
-  :ref:`C/C++ 网络编程`

这些都以附录的形式放在书末了.

另外, 还有一些难以组织到学习主线, 但是掌握了之后能提升编程体验的知识, 例如:

-  :ref:`调试工具`
-  :ref:`构建系统`
-  :ref:`单元测试`
-  :ref:`文档生成`
-  :ref:`包管理`

这些也放在附录中了.

.. graphviz:: _static/graphviz/index.gv

C/C++ 开发环境的选择
====================

本文大部分内容都是基于 Linux 上的 C/C++ 开发.
对于 Windows 上的 C++ 开发只是在必要时略提.

C/C++ 程序的开发, 需要编译器以及标准库的支持.
在 Linux 上, 系统已经自带了 GCC 编译器套件以及 glibc 标准库.
GCC 是和 Linux 同时代的产物.

Clang 是一个较新的产物, 基于 LLVM 构建. LLVM 是一个用于编写编译器的项目.
已经有许多编程语言的编译器, 解释器和代码分析工具依靠它建立了起来.
Clang 也是其中之一.

Clang 除了用于编译 C/C++ 的前端可执行程序 clang, clang++ 之外,
还提供了 clang-fmt 用于代码格式化,
lldb 用于调试,
clangd 用于语言服务器 (Language Server).

语言服务器也是一个新产物, 它是对微软提出的 LSP(Language Server Protocol) 的实现.
LSP 是连接代码分析工具与编译器的通讯协议,
它方便了不同编辑器对代码分析功能的共用.
理论上语言服务器可以为任何实现了 LSP 客户端的编辑器提供
代码补全, 格式化, 查找定义等 IDE 所实现的功能.

Clang 的编译过程分为前端的词法分析,语法分析,语义分析等, 以及后端的代码生成.
它将 C/C++ 源代码解析为 LLVM 中间语言,
然后通过后端生成二进制目标代码.

根据不同的操作系统以及 CPU 架构, Clang 会选择不同的后端.
在 Linux 上, Clang 默认以 GCC 为后端, 在 Windows 上, 则默认以 MSVC 为后端.
现在大部分个人电脑都是 64 位 x86 架构处理器, 这种架构被称作 ``x86_64``.
在终端中执行命令:

.. code-block:: bash

   clang -v

接下来就能在输出中看到::

   clang version 8.0.0 (tags/RELEASE_800/final)
   Target: x86_64-pc-linux-gnu
   Thread model: posix
   InstalledDir: /usr/bin
   Found candidate GCC installation: /usr/bin/../lib/gcc/x86_64-pc-linux-gnu/8.3.0
   Found candidate GCC installation: /usr/bin/../lib64/gcc/x86_64-pc-linux-gnu/8.3.0
   Found candidate GCC installation: /usr/lib/gcc/x86_64-pc-linux-gnu/8.3.0
   Found candidate GCC installation: /usr/lib64/gcc/x86_64-pc-linux-gnu/8.3.0
   Selected GCC installation: /usr/bin/../lib64/gcc/x86_64-pc-linux-gnu/8.3.0

等信息.

Clang 相比 GCC 的劣势, 就是历史积淀不足, 少了一些代码优化的能力.
不过对于学习者来说, 这点劣势没什么影响.

因此, 推荐使用 Clang 作为 C/C++ 开发环境.

xxd
   xxd 是系统自带的 二进制文件 <-> hexdump 转换工具.
   使用:

   .. code-block:: sh

      xxd ${filename} ${output_filename}

   或者从 stdin 输入, 向 stdout 输出.

   将文件转换为 hexdump 的形式:

   .. code-block:: hexdump

      <地址>:   <各地址上的字节>                         <字节对应的字符>
      00000000: 7f45 4c46 0201 0100 0000 0000 0000 0000  .ELF............

   .. code:: text

      $ xxd --help
      Usage:
            xxd [options] [infile [outfile]]
         or
            xxd -r [-s [-]offset] [-c cols] [-ps] [infile [outfile]]
      Options:
         -a          触发自动跳过: 单个 '*' 代替空行. 默认 off.
         -b          使用二进制 dump (和 -ps,-i,-r 不相容). 默认十六进制.
         -c cols     每一行显示的字节数目. Default 16 (-i: 12, -ps: 30).
         -E          用 EBCDIC 编码显示字符. Default ASCII.
         -e          字节小端显示 (和 -ps,-i,-r 不相容).
         -g num      一组中的字节数目. Default 2 (-e: 4).
         -i          用 C 头文件包含的格式输出.
         -l len      在 <len> 个字节后停止.
         -o off      在显示的文件中增加 <off> 个字节的偏移量.
         -ps         纯文本打印样式, 去掉了行号列和显示字符列.
         -r          逆向操作, 将 hexdump 转换为二进制文件.
         -r -s off   逆向操作时增加 <off> 个字节的偏移量.
         -s [+][-]seek  从 <seek> 个字节处开始, (使用 + 启用相对位置)
         -u          使用大写字母

objdump
   显示目标代码文件的信息. 可用于反汇编.

objcopy
   复制一个二进制文件, 有可能在进程中转换它.

readelf
   解析 ELF 文件格式.

nm
   列出文件中的符号, 默认操作文件 a.out. 输出信息由三列表格组成, 分别为 value, type, name

   -   ``value`` 都是无符号整数, 默认 16 进制显示, 对一些特殊的类型, 可能有不同的基数.
   -   ``type`` 该符号的类型:

      -   ``A`` 此符号的值是绝对的, 在之后的链接中也不会改变
      -   ``b``, ``B`` 符号位于BSS数据部分, 此部分通常包含零初始化或未初始化的数据, 但确切的行为取决于系统.
      -   ``C`` 普通符号, 是未初始化的数据, 在链接时, 多个普通符号可能同名. 此符号被视作未定义的引用.
      -   ``D``, ``d`` 此符号在初始化数据段.
      -   ``G``, ``g`` 符号位于小对象的初始化数据部分中. 某些目标文件格式允许更有效地访问小数据对象, 例如全局 int 变量而不是大型全局数组.
      -   ``i`` 对于PE格式文件, 这表示该符号位于特定于DLL实现的部分中.  对于ELF格式文件, 这表示该符号是间接函数.  这是标准ELF符号类型集的GNU扩展.  它表示一个符号, 如果由重定位引用, 则不会计算其地址, 而是必须在运行时调用.  然后, 运行时执行将返回要在重定位中使用的值.
      -   ``I`` 此符号是其他符号的间接引用.
      -   ``N`` 这是一个调试符号
      -   ``p`` 符号位于堆栈展开部分
      -   ``R``, ``r`` 符号位于只读数据段
      -   ``S``, ``s`` 符号位于小对象的未初始化或零初始化数据段
      -   ``T``, ``t`` 符号在 text(code) 数据段中. 这是机器指令数据段, 虽然它起了个令人误会的 "text" 名字.
      -   ``U`` 未定义符号
      -   ``u`` 这是一个独特的全局符号。 这是标准ELF符号绑定集的GNU扩展。 对于这样的符号，动态链接器将确保在整个过程中只有一个符号具有此名称和类型。
      -   ``V``, ``v`` 不报错的弱对象
      -   ``W``, ``w`` 未被标记的弱对象
      -   ``-`` stabs 对象, 只会在 ``.out`` 文件中定义, 提供调试信息.

ldd
   查看链接库文件的依赖关系

   .. code-block:: sh

      $ ldd libswap.so
      linux-vdso.so.1 (0x00007ffcbed0d000)
      libc.so.6 => /usr/lib/libc.so.6 (0x00007f316de60000)
      /usr/lib64/ld-linux-x86-64.so.2 (0x00007f316e042000)

鸣谢
====

感谢以下项目或人员帮助了我的程序学习经历:

.. list-table::
   :header-rows: 1

   *  -  项目或人员
      -  主页或联系方式
   *  -  Linux C 编程一站式学习
      -  http://docs.linuxtone.org/ebooks/C&CPP/c/
   *  -  free-programming-books-zh_CN
      -  https://github.com/justjavac/free-programming-books-zh_CN
   *  -  free-programming-books
      -  https://github.com/EbookFoundation/free-programming-books
