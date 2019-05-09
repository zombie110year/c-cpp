##########
链接库文件
##########

创建动态链接库
==============

DLL(Dynamic Linked Library) 是一种可在运行时被其他程序链接并执行的代码.

先以单个源文件为例, 将以下代码编译为动态链接库:

.. literalinclude:: _code/swap.c
   :language: c
   :caption: swap.c

可以使用 ``-fPIC``, ``-shared`` 等参数直接创建 ``.so`` (Shared Object) 文件:

.. code-block:: sh

   gcc -fPIC -shared -Wl,-soname,libswap.so -o libswap.so swap.c
   # 得到 libswap.so 文件

``-fPIC``
   ``-f`` 选项是很多拥有长名称的 flag 的前缀,
   PIC(Position Independent Code) 表示生成的代码不依赖于绝对地址,
   这样生成的可执行程序可以在一个动态的内存空间中执行相关的代码.
   与之相对的还有 `PIE` (Position Independent Executable)

``-shared``
   表示创建共享库.

``-Wl,-soname,libswap.so``
   ``-Wl`` 表示之后的参数传递给链接器, 用逗号作为分隔符;
   而 ``-soname,libswap.so`` 则是命名动态库, 这不是命名生成的文件,
   而是填写生成文件中的一个字段, 以便调用者识别动态库的版本.

``-o libswap.so``
   将输出写入文件 libswap.so 中

类似于单源文件, 只不过将编译和链接步骤分开执行:

.. code-block:: sh

   # 以 PIC 模式生成代码
   gcc -c -fPIC *.c
   # 将所有代码链接成动态链接库
   gcc -shared -Wl,-soname,libexample.so -o libexample.so *.o


动态链接库的链接
================

使用相关的编译器参数, 下面以显示数字的程序为例.

.. code-block:: c
   :linenos:

   #include <stdio.h>

   // 外部引用函数声明, 这会创建一个在链接时指向 libswap.so 中 swap 函数的符号.
   // 一般来说, 编译一个链接库时需要将它的头文件也共享出来
   // 像标准库头文件 stdio.h 等, 里面都是类似的声明
   extern void swap(int*, int*);

   int main(void)
   {
      int a, b;
      scanf("%d %d", &a, &b);
      swap(&a, &b);
      printf("%d %d\n", a, b);
      return 0;
   }


在编译时, 动态链接:

.. code-block:: sh
   clang -o main.out -L. -lswap main.c

``-L.``
   添加当前工作路径到链接库搜索路径, 如果将共享库文件保存到了其他路径, 则设置为对应的路径.

``-lswap``
   ``-l`` 表示链接某库. ``swap`` 是库的名字, 文件命名规则为 ``lib{name}.so[.{version}]``

要运行程序, 还需要定义环境变量 `LD_LIBRARY_PATH`_,
将 ``libswap.so`` 的路径添加到其中, 否则 ``main.out`` 仍然无法找到动态库.

.. code-block:: sh

   export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

LD_LIBRARY_PATH
---------------

一般来讲. linux系统的 ``LD_LIBRARY_PATH`` 都是未设置的. echo 出来也是空值；
这个环境变量其实是用户添加 "额外的" so 查找路径时使用. 并不会影响到系统默认的 so 查找路径;
真正的系统默认查找路径是配置在文件里的：看看你的 ``/etc/ld.so.conf`` ,
里面就配置了系统安装时. 默认的 so 查找路径. 不过这个文件一般都不直接配置查找路径.
而是简单地 import 了 ``/etc/ld.so.conf.d`` 下的所有配置文件；
再去 ``/etc/ld.so.conf.d`` 目录下看.
就会有一些 ``.conf`` 配置文件了, 这些文件里记载的路径.
就是你当前系统的 so 默认查找路径了. 这些配置跟 ``LD_LIBRARY_PATH`` 是无关的

除了设置 ``LD_LIBRARY_PATH`` 之外. 你还可以自己编辑一个 ``.conf`` 文件.
扔到 ``/etc/ld.so.conf.d`` 目录下, 也能达到添加别的路径到 ``so`` 默认查找路径的目的.  记得文件扔过去之后以 root 权限执行 ``ldconfig`` 以刷新配置
