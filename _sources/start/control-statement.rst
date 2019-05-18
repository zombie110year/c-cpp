########
控制语句
########

if-else 分支
============

如果要在某个情况下才运行某段代码, 可以使用一个 ``if`` 结构::

   if(expr) {
      // expr == true 时运行
   }
   // 其他代码

只有在 表达式 ``expr`` 的值为 true 时, 花括号中的代码才会被运行.
而当 expr 为 false 时, 花括号中的代码不会被运行, 将会被跳过.

.. note:: true 和 false 称作 *布尔数*, 只有 "真", "假" 两个值.

   在 C 语言中, 任何整数都可以当作布尔数使用,
   当它们为 0 时, 等于 "假",
   在其他情况下都为 "真".

   C 标准使用整数 1, 0.

``if`` 结构也可以不使用花括号, 但是这样只能控制一个语句的执行条件::

   if(expr)
      // 一行语句

也可以不换行::

   if(expr) // 一行语句

当只需要控制一条语句时, 当然可以不使用花括号, 但是如果之后需要修改,
要增添一些语句, 那么再加花括号是很麻烦的.
为了少些麻烦, 推荐在任意时刻都使用花括号.

如果要求这样的一个结构: 当条件满足时, 执行分支 A, 条件不满足时执行分支 B,
那么可以使用 ``if-else`` 的分支结构::

   if(expr) {
      // true
   } else {
      // false
   }

如果要对一个区间进行判断与控制, 可以嵌套 if-else 结构::

   if(assignment < 60) {
      printf("不及格\n");
   } else if (assignment < 80) {
      printf("C\n");
   } else if (assignment < 90) {
      printf("B\n");
   } else {
      printf("A\n");
   }

在每一层 if-else 结构中, else 部分没有使用花括号, 如果加上花括号, 就能更明显地看出嵌套关系::

   if (assignment < 60) {
      printf("不及格\n");
   } else {
      if (assignment < 80) {
         printf("C\n");
      } else {
         if (assignment < 90) {
            printf("B\n");
         } else {
            printf("A\n");
         }
      }
   }

switch 分支
===========

switch 分支和 if-else 相比, 同样适合对多分支情形进行处理, 不过, switch 只能处理离散情况::

   switch (expr) {
      case cond_1: // 分支 1
      case cond_2: // 分支 2
      case cond_3: // 分支 3
         break;
      default:
         // 默认分支
         break;
   }

switch 语句中的判断表达式 expr 应当具有整数值,
将从上到下地与 ``cond_1``, ``cond_2`` 等分支进行比较,
如果 expr 的值与 cond_x 相等, 则会进入此分支向下执行,
直到 ``break;`` 或者到达语句末尾.
``break`` 是 C 语言关键字, 用于中断 switch 分支或者循环结构.
如果一个分支中没有 break, 则程序在执行完此分支后, 会跳入下一个分支继续执行.
有些时候这个特性很有用.

关键字 ``case`` 后的判别量必须是编译期间可以确定的常量 (const 或者 字面值).

default 分支不是必须的, 它的作用是当 expr 的值无法与任何分支匹配时, 进入此分支执行.

while 循环
==========

要循环执行一段语句, 可以使用 while 循环或者 `for 循环`_,
while 循环的语法如下::

   while(expr) {
      // loop-body
   }

另外还有一个 do-while 循环::

   do {
      // loop-body
   } while (expr)

while 循环将会判断表达式 expr 的值, 当 expr 为 "真" 的时候, 就会执行 loop-body 中的语句.
而 do-while 呢, 则是先执行一遍, 再进行判断.

for 循环
========

for 循环比 while 循环更复杂一点, 它可以使用三个表达式::

   for (/* init */; expr ; /* loop-end */) {
      // loop-body
   }

-  ``init`` 表达式会在整个循环开始时执行一次, 总共只会执行这一次.
   在大多数使用情况下, 会在这里进行循环控制变量的定义.
-  ``expr`` 表达式就是此循环的判定表达式, 和其他控制结构相同.
-  ``loop-end`` 是在每一次 loop-body 执行完毕后执行一次,
   一般在这里进行循环控制变量的修改.

下面是一个求 1-100 的整数和的例子::

   int sum = 0;
   for(int i = 1; i <= 100; ++i) {
      sum += i;
   }

值得注意的是, 在 init 表达式中定义的变量只能在这个 for 结构中访问.
处于 for 循环的块级作用域中.
在其他控制结构中也可以定义变量, 但是都不能在花括号外访问,
这是因为花括号就是作用域的界定符.
详细讨论见 :ref:`作用域`.

break 与 continue
=================

break 和 continue 是用于控制条件分支或者循环语句的关键字.
和它们的字面含义一致, 分别表示 "中断", "继续" 的含义.

break 可以使用在 switch 分支和 while, do-while, for 循环之中,
将会中断并跳出当前控制结构.

continue 可以使用在循环结构中, 作用是在此处中断, 并提前进入下一回合循环.
对于 for 语句, loop-end 仍然会被执行.

.. _`三目条件表达式`:

三目条件表达式
==============

操作符 ``?:`` 可以起到类似于 if-else 语句的效果::

   result = c ? x : y;

等价于::

   if(c) {
      result = x;
   } else {
      result = y;
   }
