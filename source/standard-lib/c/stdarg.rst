########
stdarg.h
########

stdarg 提供了可变长参数功能.

类型
====

.. c:type:: va_list

   一个可变长的参数列表.

宏
==

.. c:macro:: va_start(ap, param)

   初始化 :c:type:`va_list` 参数列表.
   可变长参数必须初始化后使用.

   :param ap: 需要初始化的 va_list 变量.
   :param param: 最后一个固定参数.


.. c:macro:: va_arg(ap, type)

   从可变长参数列表 ap 中获取下一个 type 类型的参数.

   如果 ap 中有不同类型的参数,
   且 type 未改变,
   则对应位置的参数会被跳过,
   并且可能访问越界.

   :param ap: 可变长参数列表.
   :param type: 下一个获取的参数值的类型.

.. c:macro:: va_end(ap)

   释放参数列表 ap 占用的内存.

.. c:macro:: va_copy(dest, src)

   将 src 复制到 dest 当中.
   src 的读取状态也会被复制.
   dest 将无法获取已经被 src 提取过的参数.

   :param dest: 复制品
   :param src: 原版
   :type dest: va_list
   :type src: va_list

示例
====

.. literalinclude:: _code/stdarg.show.c
   :linenos:
   :language: c

定义函数时在形参表使用 ``...`` 省略号表示使用 va_list 传递参数.

.. literalinclude:: _code/stdarg.call.c
   :caption: 将 va_list 通过参数传递给其他函数
   :linenos:
   :language: c

C 语言中的 :c:type:`va_list` 会记录当前函数帧栈上的形参表的地址.

当一次函数调用时, 会在调用栈上为被调用的函数压入一个帧.
帧上为此函数作用域中所声明的所有变量都分配了空间, 包括函数的形参.
并且形参是按顺序依次排列的, 这被称作 "形参表".

当使用 :c:type:`va_list` 时, 你需要通过宏 :c:macro:`va_start` 来找到可变形参的位置::

   va_start(args, count);

这一步就是在告诉编译器:

1. 找到当前栈帧上的形参表中参数 ``count`` 的位置
2. 把 ``count`` 的地址告诉 :c:type:`va_list` 类型的 ``args``

因此, 使用 :c:macro:`va_start` 初始化之后, ``args`` 就可以直接找到不定量形参的位置.

在读取参数时, 调用 :c:macro:`va_arg` 宏,
它就是读取 ``args`` 当前记录的地址,
然后以输入的类型来解读它,
并且将 ``args`` 所记录的地址修改到新的位置.

所以可以将 :c:macro:`va_start` 初始化过的 ``args`` 通过函数调用传递.
哪怕产生了新的帧, ``args`` 也是记录着上次初始化时所记录的地址.
