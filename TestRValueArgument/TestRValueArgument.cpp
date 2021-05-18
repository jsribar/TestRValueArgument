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

void FuncRValueRef(MyClass&& mc)
{
    MyClass m = std::move(mc);
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

class B
{
public:
    B(MyClass&& mc)
        : m(std::move(mc))
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
    std::cout << "FuncRValueRef\n";
    FuncRValueRef(std::move(mc3));

    std::cout << "FuncRValueRef\n";
    FuncRValueRef(MyClass{});

    B b{ MyClass{} };

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
