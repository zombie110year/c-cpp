############
被扩展的函数
############

函数重载
========

在 C++ 中，一个函数名可以重复使用，但要求其返回类型以及参数类型不同。
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
