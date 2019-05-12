##############
结构体与联合体
##############

结构体和联合体可以构造比基本类型复杂的数据类型.

结构体
======

结构体可以包含复数个成员, 这些成员按照声明顺序分别占用对应大小的内存空间.
不过, 由于存在 *内存对齐(Memory Align)* 机制, 小于一个字长而未被使用的部分将留空.
内存对齐也是在 x86_64 平台上, 一个对象的地址总是 4 (int 类型的长度) 的倍数的原因.

结构体会创建一个新的类型, 如下::

   struct name {
      int member1;
      int member2;
   };

这会创建一个名为 ``struct name`` 的新类型, 可以用来声明变量::

   struct name var;

也可以定义匿名结构体, 并同时声明变量::

   struct { int length, int *body } array;

这声明了一个名为 ``array`` 的变量, 它具有 ``length`` 与 ``body`` 两个成员.

也可以使用 typedef 为结构体或匿名结构体类型声明别名::

   typedef struct name name_t;
   typedef struct {int length, int *body} int_array_t;

xxx_t 是 GNU 的命名习惯, 实际上可以命名为任何标识符.

联合体
======

联合体使用 union 关键字. 它可以用一个位置存储多种类型的值.
一次只能存储一个值, 而整个内存区域的大小取决于最大的成员::

   union nubmer_t {
      int x;
      double x;
   };

用例
====

.. literalinclude:: _code/show.struct-union.c
   :language: c
   :caption: show.struct-union
   :linenos:
