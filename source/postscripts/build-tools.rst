########
构建工具
########

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

CMake 基本概念
--------------

-   CMake 中的命令不区分大小写
-   CMake 使用 ``set`` 命令设置变量
-   CMake 使用 ``${varname}`` 的形式引用变量
-   对于多个元素, 可以使用空格分隔

必需命令
--------

cmake_minimum_required(必需)
****************************

cmake_minimum_required 命令用于设置 CMake 最低所需要的版本, 语法:

.. code:: cmake

    cmake_minimum_required(VERSION <min>[...<max>])

-  设置最低版本

.. code:: cmake

    cmake_minimum_required(VERSION 3.14.0)

-  设置在两个版本之间

.. code:: cmake

    cmake_minimum_required(VERSION 3.0.0..3.14.0)


project(必需)
**************

`project <https://cmake.org/cmake/help/latest/command/project.html>`_
设置项目信息. 在顶层模块中, 这是必需的设置.

.. code:: cmake

    project(<PROJECT-NAME>
            [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
            [DESCRIPTION <project-description-string>]
            [HOMEPAGE_URL <url-string>]
            [LANGUAGES <language-name>...])

这会设置一个变量 ``PROJECT_NAME``, 它的值也是参数 ``<PROJECT_NAME>``
的值. 同时, 也会产生另外两个相关的变量:

-   ``<PROJECT_NAME>_SOURCE_DIR``
-   ``<PROJECT_NAME>_BINARY_DIR``

例如:

.. code:: cmake

    project(helloworld)

则会产生:

.. code:: sh

    ${PROJECT_NAME} # helloworld
    ${helloworld_SOURCE_DIR}
    ${helloworld_BINARY_DIR}

对于顶层模块, 则有:

.. code:: sh

    PROJECT_SOURCE_DIR = ${<PROJECT_NAME>_SOURCE_DIR}
    PROJECT_BINARY_DIR = ${<PROJECT_NAME>_BINARY_DIR}

生成目标
--------

为一个项目添加生成目标, 可执行文件、链接库文件等.

add_executable
**************

`add_executable <https://cmake.org/cmake/help/latest/command/add_executable.html>`_
为项目添加一个可执行目标:

.. code:: cmake

    add_executable(<name> [WIN32] [MACOSX_BUNDLE]
                    [EXCLUDE_FROM_ALL]
                    [source1] [source2 ...])

-   ``<name>`` 设置为可执行文件的命名, 在 Windows 上, 会自动添加 ``.exe``
    后缀.
-   ``EXCLUDE_FROM_ALL`` 设置是否在生成的 Makefile 中的 ``all``
    目标中将此目标排除. 如果设置了此变量, 则排除, 需要单独
    ``make <name>`` 进行构建, 否则将被包含.
-   ``sources ...`` 是一个源文件列表, 也可以使用变量来指定, 常用
    _`aux_sources_directory` 来将一个目录下的所有源文件设置到一个变量中.

这会创建一个与 ``<name>`` 同名的变量, 指向这个目标.

-   ``WIN32`` 选项如果设置, 则会创建属性 ``WIN32_EXCUTABLE``,
    这会将程序的入口从 main 函数修改为 WinMain 函数.

add_library
***********

`add_library <https://cmake.org/cmake/help/latest/command/add_library.html>`_
将对应的源代码设置为链接库目标:

.. code:: cmake

    add_library(<name> [STATIC | SHARED | MODULE]
                [EXCLUDE_FROM_ALL]
                [source1] [source2 ...])

-   ``<name>`` 是该生成目标的命名, 会自动添加相应的前缀/后缀名. 例如
    ``lib<name>.a``, ``<name>.lib`` 等.
-   ``STATIC | SHARED | MODULE`` 三选一, 设置该目标的库类型 (静态链接库归档
    \| 动态链接库 \| 未链接到其他目标的插件，但可以在运行时使用类似
    ``dlopen`` 的函数动态加载)

这会创建一个与 ``<name>`` 同名的变量, 指向这个目标.

target_link_library
*******************

`target_link_library <https://cmake.org/cmake/help/latest/command/target_link_libraries.html>`_
设置一个链接关系.

.. code:: cmake

    target_link_libraries(<target> ... <item>... ...)

将 ``<item>`` 链接到 ``<target>`` 上. ``<item>``
``<item>`` 是一个用空格分隔的列表.

模块化
------

可将源代码分别保存在不同的文件夹中, 每一个文件夹下都创建一个 CMakeLists.txt 文件,
这样的一个文件夹被 CMake 认为是一个 subdirectory.

add_subdirectory
****************

`add_subdirectory <https://cmake.org/cmake/help/latest/command/add_subdirectory.html>`_
将一个子目录添加进来. 典型的 CMake 构建项目将类似于一个树状结构,
顶部目录的 CMakeLists.txt 将作为 根, 而各级子目录中的 CMakeLists.txt
则作为 分支与叶, 最终构建整个项目.

.. code:: cmake

    add_subdirectory(<source_dir> [<binary_dir>] [EXCLUDE_FROM_ALL])

子目录中的 CMakeLists.txt 将被立刻解析, 并 “嵌入” 到当前位置.

-   ``<source_dir>`` 设置此模块的源码路径(即 CMakeLists.txt 所在路径),
    可以是相对或绝对路径. 相对路径是相对于当前文件.
-   ``<binary_dir>`` 设置此模块的二进制生成路径, 如果不进行设置, 则设置为
    ``<source_dir>``. 可以是相对或绝对路径.

编译选项
--------

add_compile_options
*******************

`add_compile_options <https://cmake.org/cmake/help/latest/command/add_compile_options.html>`_
添加编译器选项.

.. code:: cmake

    add_compile_options(<option> ...)

例如

.. code:: cmake

    if (MSVC)
        # warning level 4 and all warnings as errors
        add_compile_options(/W4 /WX)
    else()
        # lots of warnings and all warnings as errors
        add_compile_options(-Wall -Wextra -pedantic -Werror)
    endif()

add_link_options
****************

`add_link_options <https://cmake.org/cmake/help/latest/command/add_link_options.html>`_
添加链接器选项.

add_definitions
***************

`add_definitions <https://cmake.org/cmake/help/latest/command/add_definitions.html>`_
添加宏定义.

.. code:: cmake

    add_definitions(-DFOO -DBAR ...)

include_directoies
******************

`include_directories <https://cmake.org/cmake/help/latest/command/include_directories.html>`_
添加头文件搜索路径.

.. code:: cmake

    include_directoies(lib/include)

link_directoies
***************

`link_directories <https://cmake.org/cmake/help/latest/command/link_directories.html>`_
添加库文件搜索路径.

.. code:: cmake

    link_directoies(lib)

常用命令
--------

aux_source_directory
********************

`aux_source_directory <https://cmake.org/cmake/help/latest/command/aux_source_directory.html>`_
.. code:: cmake

    aux_source_directory(<dir> <variable>)

将 ``<dir>`` 中的源文件扫描, 保存到变量 ``<variable>`` 中.

set 与 unset
*************

`set <https://cmake.org/cmake/help/latest/command/set.html>`_
设置变量.

常用的预定义变量有:

-   ``EXECUTABLE_OUTPUT_PATH``: 生成的可执行文件保存的路径
-   ``LIBRARY_OUTPUT_PATH``: 生成的库文件保存的路径
-   `CMAKE_BUILD_TYPE <https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html>`_:
    构建类型, 有 ``Debug``, ``Release``, ``MinSizeRel`` 等级别.

也可以在生成构建脚本时, 使用 ``-Dkey=value`` 的形式在命令行中设置
(cmake 宏定义, 注意不要与 gcc 等编译器宏定义混淆):

.. code:: sh

    cmake -DCMAKE_BUILD_TYPE=Release ..

使用 ``unset`` 删除一个变量.

脚本语法
--------

`脚本语法 <https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html#scripting-commands>`_
可以为 CMake 脚本添加一些逻辑功能:

if-else
*******

`if 语句 <https://cmake.org/cmake/help/latest/command/if.html>`_:

.. code:: cmake

    if(<condition>)
        #<commands>
    elseif(<condition>) # optional block, can be repeated
        #<commands>
    else()              # optional block
        #<commands>
    endif()

cmake 命令行选项
================

除了在 CMakeLists.txt 中编辑, cmake 在命令行中也暴露了一些功能.

定义一个变量
------------

效果和在 CMakeLists.txt 中编写 ``set()`` 命令是一样的.

.. code:: sh

    cmake -D <key>=<value>
    # or
    cmake -D <key>:<type>=<value>

设置生成器
----------

选择生成 Makefile, VS 工程, 或者其他构建系统的文件:

.. code:: sh

    cmake -G "<Generators>"

常用的有:

-   ``MinGW Makefiles``: MinGW 环境下的 Makefile,
-   ``MSYS Makefiles``: 如果使用 msys2, 使用这个, 不要用 ``MinGW Makefiles``,
    因为 msys2 中的 sh.exe 会导致 cmake 对路径的推断出现误判.
-   ``Visual Studio 16 2019``: VS 2019 下的解决方案(``.sln`` 文件)
-   ``Unix Makefiles``: Unix 系统中的 Makefile.

在不同的系统下, 默认生成器不同, 在 Linux 中, 默认 Unix Makefiles, 在 Windows
系统中, 则是 VS 解决方案.

使用 graphviz 生成依赖关系图
----------------------------

.. code:: sh

    cmake --graphviz=output.gv

得到 graphviz 标记语言文件, 可以继续使用 graphviz 工具得到图片.

https://cmake.org/cmake/help/latest/module/CMakeGraphVizOptions.html
