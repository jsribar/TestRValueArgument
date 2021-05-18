// TestRValueArgument.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class MyClass
{
public:
    MyClass()
    {
        a = ++counter;
        std::cout << "Default constructor\n";
    }

    MyClass(const MyClass& other) : a(other.a)
    {
        std::cout << "Copy constructor\n";
    }

    MyClass(MyClass&& other) noexcept : a(other.a)
    {
        std::cout << "Move constructor\n";
    }

    int a{ 99 };

    static int counter;
};

int MyClass::counter = 0;

void FuncConstRef(const MyClass& mc)
{
    std::cout << mc.a << std::endl;
}

void FuncRValueRefWithMove(MyClass&& mc)
{
    MyClass m = std::move(mc);
    std::cout << m.a << std::endl;
}

void FuncRValueRefWithoutMove(MyClass&& mc)
{
    MyClass m = mc;
    std::cout << m.a << std::endl;
}

void FuncValue1(MyClass mc)
{
    std::cout << mc.a << std::endl;
}

void FuncValue2(MyClass mc)
{
    MyClass m = std::move(mc);
    std::cout << m.a << std::endl;
}

class WithMove
{
public:
    WithMove(MyClass&& mc)
        : m(std::move(mc))
    {}
private:
    MyClass m;
};

class WithoutMove
{
public:
    WithoutMove(MyClass&& mc)
        : m(mc)
    {}
private:
    MyClass m;
};


int main()
{
    MyClass mc1;

    std::cout << "FuncConstRef\n";
    FuncConstRef(mc1);

    MyClass mc2;
    std::cout << "FuncValue1\n";
    FuncValue1(mc2);

    std::cout << "FuncValue1\n";
    FuncValue1(std::move(mc2));

    MyClass mc4;
    std::cout << "FuncValue2\n";
    FuncValue2(mc4);

    std::cout << "FuncValue2\n";
    FuncValue2(std::move(mc4));

    MyClass mc3;
    std::cout << "FuncRValueRefWithoutMove\n";
    FuncRValueRefWithoutMove(std::move(mc3));

    MyClass mc5;
    std::cout << "FuncRValueRefWithMove\n";
    FuncRValueRefWithMove(std::move(mc5));

    std::cout << "FuncRValueRefWithoutMove\n";
    FuncRValueRefWithoutMove(MyClass{});

    std::cout << "FuncRValueRefWithMove\n";
    FuncRValueRefWithMove(MyClass{});

    WithoutMove wm0{ MyClass{} };

    WithMove wm{ MyClass{} };
}
