############
被扩展的函数
############

函数重载
========

在 C++ 中，一个函数名可以重复使用，但要求其参数类型不同。对返回值类型没有要求。
这种特性被称为 **函数重载**。

.. code:: cpp

    #include <iostream>
    using namespace std;

    class NumberComparer {
        public:
        double max(double a, double b) { return a > b ? a : b; }
        int    max(int a, int b) { return a > b ? a : b; }
    };

    int Max(int a, int b) { return a > b ? a : b; }

    double Max(double a, double b) { return a > b ? a : b; }

    int main(void) {
        NumberComparer cmp;
        cout << cmp.max(1, 2) << endl;
        cout << cmp.max(3.0, 4.0) << endl;
        cout << Max(1, 2) << endl;
        cout << Max(9.0, 16.0) << endl;
        return 0;
    }

.. danger::

    如果你将 ``double`` 贸然改成 ``float`` 会导致报错:

    .. code:: text

        error: call of overloaded 'max(double, double)' is ambiguous
            cout << cmp.max(3.0, 4.0) << endl;

    这是因为浮点数字面量的默认类型是 double，而找不到相关的实现。

实际上，在符号解析时，C++ 编译器会根据返回类型，形参类型以及形参顺序修改符号名，例如 ``int Max(int, int)`` 在解析后可能就变成了 `int_Max_int_int` 等等。

C++ 的泛型和函数重载是一样的原理：编辑器统计调用泛型函数的情况，自动生成不同类型函数的代码。

接下来，分别看一个重载的例子:

.. literalinclude:: _code/overload.show.cpp
    :language: cpp
    :linenos:

.. literalinclude:: _code/overload.show.s
    :language: asm
    :linenos:
    :emphasize-lines: 6,37

可以看到， ``int abs(int)`` 在编译时被命名为了 ``_Z3absi``, 而 ``double abs(double)`` 则被编译为 ``_Z3absd``。
其返回值类型没有在符号名中体现出来，这也表达了 C++ 中函数重载对返回值类型不做要求的性质。

泛型函数
========

在定义一个泛型函数时，使用这样的语法:

.. code-block:: cpp

    template <typename /*模板名*/>
    /* 返回类型 */ /* 函数名 */(/* 形参表 */) {
        /* 函数体 */
    }

实际上就是在正常的函数定义上添加一行:

.. code:: cpp

    template <typename T>

然后，就可以在 **返回类型**、**形参表** 和 **函数体** 中选择性地使用这个类型模板来代表所有类型。

例如:

.. code-block:: cpp

    #include <iostream>
    using namespace std;

    template <typename T>
    T Max(T a, T b) { return a > b ? a : b; }

    int main(void) {
        cout << Max(1, 2) << endl;
        cout << Max(9.0, 16.0) << endl;
        return 0;
    }

这样，当调用 ``int Max(int, int)`` 时，会自动生成相关的代码；调用 `double Max(double, double)` 时也一样。

也可以在定义中的一些地方将类型写死，例如:

.. code-block:: cpp

    template <typename T>
    bool greatter(T a, T b) {return a > b};

这样，调用 greatter 函数时，返回值一定是 ``bool`` 类型。
在形参表、函数体中也是一样。

有些时候，需要定义多种不同的模板，可以像这样：

.. code:: cpp

    template <typename T, typename S>
    template <typename A, typename B/* , ... */>
    // ...

如果不能确定需要多少种模板？这种情况建议用联合体来实现。

constexpr
=========

有一些表达式，无论在任何情况下都能求出唯一的值，并且没有任何副作用，这种表达式实际上在编译期间就会被编译器优化为静态常量。

但是如果希望在程序中多处调用的话，就不得不重复书写相同的表达式。

由于在栈上定义的数组是在编译期就分配内存的，因此它的长度必须是一个静态常量，我们可以利用这一性质来检验常量表达式。

.. code:: cpp

    int main(void) {
        int arr[1 + 3 * 5]; // 长度为 16
        return 0;
    }

在过去，常使用宏定义来解决这个问题:

.. code:: cpp

    #define LENGTH (1+3*5)

    int main(void) {
        int arr[LENGTH];
        return 0;
    }

但是宏定义一方面比较复杂，另一方面又没有类型，容易出错。

C++ 11 推出了 constexpr 声明，以解决这个问题。

.. code:: cpp

    constexpr int length () {
        return 1 + 3 * 5;
    }

    int main(void) {
        int arr[length()];
        return 0;
    }

加了 constexpr 的函数将会被编译器优化掉，直接计算出值并存储在静态区。但是它只能是一个表达式，不能使用流程控制语句，定义局部变量等。

接下来就是 constexpr 厉害的地方了。它可以：

1. 传入参数，参数也必须是 static const 值
2. 定义局部变量，但不能访问堆，而且栈只会在编译期存在。
3. 递归调用，但只能调用同为 constexpr 的函数
4. 在内部可以使用局部变量和流程控制语句（C++14）

.. code:: cpp

    constexpr int length() {
        return 1 + 3 * 5;
    }
    constexpr int fib(const int n) {
        return n == 1 || n == 2 ? 1 : fib(n - 1) + fib(n - 2);
    }
    int main(void) {
        int arr0[length() + 10];
        int arr1[fib(10)];
        return 0;
    }

在 C++14 后， constexpr 就不局限于单独一条 return 语句了，它可以这么写:

.. code:: cpp

    #include <iostream>
    constexpr int fib(const int n) {
        switch (n) {
        case 1:
        case 2:
            return 1;
        default:
            return fib(n - 1) + fib(n - 2);
        }
    }
    int main(void) {
        int arr1[fib(10)];
        std::cout << fib(10) << std::endl;
        return 0;
    }


inline
======


调用运算符
==========

在 C++ 中, 函数和类的边界变得模糊了. 任何实现了 **调用运算符** ``operator()`` 的对象,
都可以当作函数来使用.

C++ 中的闭包（匿名函数）便是利用一个重载了调用运算符的匿名类实例来实现的。

匿名函数
========

匿名函数、闭包、lambda 表达式等等名称，指的都是同一样东西。它的声明方式如下：

.. code:: cpp

    [/* 捕获外部变量 */](/* 形参表 */)
    /* mutable */ /* 异常设定 */ -> /* 返回类型 */
    {/* 函数体 */};

- **捕获外部变量**：将当前作用域可以访问的变量添加到匿名函数内部的作用域中。

    1. 不需要类型声明符，各变量用逗号分隔。
    2. 可用 ``=`` 表示以复制的形式捕获所有需要的外部变量, ``&`` 表示以引用的形式捕获外部变量。
    3. 如果要以引用的方式捕获指定变量，例如引用变量 ``a``: ``&a``。

- **形参表**：和正常函数的形参表功能一致。
- **mutable**：如果留空，则默认不可修改捕获的变量。当用复制方式捕获变量时，此设置无意义。
    当设置为 ``mutable`` 时，可以修改引用的外部变量。
- **异常设定**：
- **返回类型**： 和正常函数一致。当省略时可由编译器自动推导。
- **函数体**： 和正常函数一致。

可以直接调用:

.. code:: cpp

    /* lambda expresison*/(/* arguments */);

也可以赋值给一个变量，然后将此变量当作函数一般使用:

.. code:: cpp

    auto lambda = /* lambda expression */;
    lambda(/* arguments */);

.. code-block:: cpp

    #include <iostream>
    using namespace std;

    int main(void) {
        auto lambda = [](float a, float b) -> float { return a; };
        cout << lambda(1.0f, 2.0f) << endl;
        cout << [] { return 0; }() << endl;
        return 0;
    }

上面的例子是完整例子，实际使用时某些项目可以省略，常常使用这三种形式:

.. code:: cpp

    [](/* 形参表 */) {
        /* 函数体 */
    };

    [/* 捕获 */](/* 形参 */) {
        /* 函数体 */
    };
    [/* 捕获 */] {
        /* 函数体 */
    };

虽然对于基本数据类型，编译器都能成功推导，但在把不准时建议还是手动指定返回类型。

extern "C"
==========

上面 `函数重载`_ 中提到了 C++ 编译器会将函数的参数也编译进符号名中，这和 C 编译器的行为是不一样的。
C 编译器只会将函数名编译进符号名。
C 语言作为老前辈，有许多语言使用 C 风格的 FFI（Foreign Function Interface）调用 C 编译的库。
为了让 C++ 也能为这些语言所用，编译器就提供了 ``extern "C"`` 声明::

    extern "C" {
        int add(int a, int b) {
            return a + b;
        }
    }

在 ``extern "C"`` 代码块中定义或声明的函数，将会使用 C 风格的符号命名，例如:


.. literalinclude:: _code/extern_c.show.cpp
    :language: cpp
    :linenos:

.. literalinclude:: _code/extern_c.show.s
    :language: asm
    :linenos:
    :emphasize-lines: 15,38,61

类型名后置
==========

在 C++ 中，定义函数时可以将类型名写在后面：

.. code:: cpp

    auto one() -> int {
        return 1;
    }
