########
assert.h
########

assert.h 头文件中只提供了一个宏函数 :c:func:`assert` 使用.
这个函数将判断传入的表达式的布尔值,
如果判断为假, 则中断程序并输出调试信息.

.. c:function:: assert(expr)

   - 如果 expr 表达式的值为 true , 则没有影响
   - 如果 expr 表达式的值为 false, 则终止程序并打印代码所运行的文件路径与行号
