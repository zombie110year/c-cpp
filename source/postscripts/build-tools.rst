构建工具
========

如果 C/C++ 的各源代码分散在不同的 *.c* 或 *.cpp* 文件中, 在编译后又生成多个需要链接的 *.o* 文件.
如果每次都在命令行中运行 ``gcc *****`` 等命令, 那无疑是在浪费人类宝贵的生命.

因此, 构建工具应运而生, 最早的 C/C++ 构建工具应该是 make, 这是一种 **命令式** 的构建工具.
其使用方法就是, 在项目中编写 Makefile, 设置一些变量, 设置一些互相依赖的目标或文件,
对每一个目标分别编写完成此目标需要执行的命令.
而 make 可执行程序在读取并解析 Makefile 之后, 按照依赖顺序依次执行这些命令.
make 相当智能, 它能够分辨哪些文件需要更新, 哪些目标需要重做, 在目前仍然流行.

例如, 对于一个项目, 如果我们用这几行命令编译的话:

.. code:: sh

    # 编译 object
    gcc -c caculate.c -g -O0
    gcc -c main.c -g -O0
    # 链接 object 与 libm
    gcc -o main.out hello.o caculate.o -lm

那么, 就可以编写这样的 Makefile:

.. sidebar:: Makefile 简单介绍

    编写规则时使用的语法大致为:

    .. code:: text

        <目标>: <依赖>
            <命令>

    -   ``$()`` 引用一个变量
    -   ``$<``, ``$@``, ``$^`` 等是预设变量, 分别表示 最左依赖, 生成目标, 所有依赖
    -   没有赋值的变量将为空
    -   引用变量可以认为是将变量的值填充到命令行中构成命令, 行为类似于字符串格式化
    -   CC, CFLAGS, CPPFLAGS 是 C 编译器命名习惯, 分别表示编译器, 编译选项, 预处理选项

    想要学习 Makefile 的话, 可以阅读陈浩编写的
    `跟我一起写 Makefile <https://github.com/seisman/how-to-write-makefile>`_.

.. code:: makefile

    CC = gcc
    CFLAGS = -g -O0
    CPPFLAGS =

    main.out: main.o caculate.o
        $(CC) -o $@ $(CFLAGS) $^ -lm

    main.o: main.c main.h caculate.h
        $(CC) -c $< $(CFLAGS) $(CPPFLAGS)
    caculate.o: caculate.c caculate.h
        $(CC) -c $< $(CFLAGS) $(CPPFLAGS)

编写时, 一般先在头部定义好关于编译器、编译选项、安装位置、项目名称等重要信息, 然后在
之后的命令中引用, 这样定义的话, 日后修改起来也更方便. 文件中的第一条规则是默认规则,
一般把项目最终产品 -- 可执行程序、依赖库或其他, 放在第一条. 运行命令行:

.. code:: sh

    make

后就会从默认规则开始执行, 除非在之后的命令行参数中指定要 make 的目标才会改变依赖树的起点.
规则的编写顺序并不重要, make 程序会自动解析依赖关系.

不仅仅局限于 C/C++ 项目, 由于 Makefile 是命令式的, 拥有相当强的自定义能力,
你可以将任何命令行工具组织在其中. 例如本书使用的 Sphinx Doc 就使用了一个 Makefile
来将 RST 源代码编译为 HTML、PDF、EPUB 等格式.

但 make 也有一些问题, 例如, 对于不同的系统架构, 不同的编译环境, 都需要修改一些设置,
并且, 不同的 Linux 发行版中安装的依赖库版本位置都有可能不同, 因此需要不同的 Makefile.
虽然也可以在同一个 Makefile 中书写相关的规则来自动判断不同的设置, 但这样 Makefile 很
容易变得过度复杂, 无法维护. 因此 GNU 组织编写了 autotools 工具集, 创建了 M4 宏语言,
来简化推断编译条件的过程. 但这又引入了新的宏语言, 增加了学习难度. 到目前大部分 C 项目
都不再使用 autotools 了, 人们需要更简单的工具.

**命令式** 工具还是太过复杂了, 之后出现了 **声明式** 的构建脚本.
所谓声明式, 就是说只要在脚本中配置好项目的名称, 有哪些源文件, 要链接哪些依赖库, 用什么编译器...
等等即可. 而具体的执行步骤则由构建系统自动决定.

现代 C/C++ 的构建工具可谓是百花齐放, 有的集成了包管理, 有的可以分布式编译, 有的集成了测试工具,
有的还表示 "我全都要"... 在 GitHub 上一个 `Awesome C++ <https://github.com/fffaraz/awesome-cpp#build-systems>`_
列表中记录了十几个构建工具. 其中 CMake 流行度最高, 大多数 C/C++ 项目都使用它, 但其他编译工具的用户量也不少.

这些构建工具都有一定的使用特征, 例如, 要通过这些命令行编译的, 应当是 GNU autotools 了:

.. code:: sh

    ./configure
    make

而在项目中, 有配置文件 *CMakeLists.txt* 的, 就是 CMake 无疑了.
在项目中有 *Solution.sln* 的 -- 这是 Visual Studio 创建的项目, 你也可以用 MSBuild 来构建他.

各工具具体间的差异可以阅读网络上的评测文章, 本书介绍 CMake 的使用方法.

CMake
=====

CMake 的工作流程是:

1. 读取 CMakeLists.txt 中的设置
2. 使用 cmake 生成 Makefile 等脚本, 交给 make 执行

除了用于生成 Makefile 的 cmake, CMake 工具包还提供了打包安装包的 cpack,
利用 stdio 进行简单测试的 ctest.
