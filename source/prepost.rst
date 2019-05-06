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
