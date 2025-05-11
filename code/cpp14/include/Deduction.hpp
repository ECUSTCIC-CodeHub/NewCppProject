#pragma once

#include "../Reflect.hpp"
#include "PrintType.h"
#include <map>
#include <memory>
#include <vector>

class autoTest
{
public:
    void testBaseType()
    {
        std::cout << "----------------" << std::endl;
        std::cout << "基本类型推导" << std::endl;
        auto a = 1;     // int
        auto b = 2.f;   // 
        auto c = new int[3] {1, 2, 3}; // int*
        double tmp_d = 3.0; // double
        auto d = tmp_d;     // double
        PrintType2(a); PrintType2(b); PrintType2(c); PrintType2(d);
    }

    void testContainer()
    {
        std::cout << "\n----------------" << std::endl;
        std::cout << "模板类型推导" << std::endl;
        auto a = { 1, 2, 3 };                   // std::initializer_list<int>
        auto b = std::vector<int>{ 1, 2, 3 };   // std::vector<int>
        auto c = std::map<int, int>{ {1,1} };   // std::map<int, int>
        auto d = std::make_unique<int[]>(3);    // std::unique_ptr<int[]>
        PrintType2(a); PrintType2(b); PrintType2(c); PrintType2(d);
    }

    void testLambda()
    {
        std::cout << "\n----------------" << std::endl;
        std::cout << "函数推导" << std::endl;
        const int a = 1;
        const int b = 2;
        // lambda本质是一个类
        auto lambda = [](const int a, const int b) { return a; };
        // lambda的返回值是用auto推导的，不带引用和限定符
        auto lambda2 = [](const int a, const int b) { if (b > 0) return a; else return b; };
        auto  result = lambda(1, 2); // int
        auto func_ptr = &autoTest::func; // int (autoTest::*)(int, const int&, int*)

        PrintType2(lambda); PrintType2(result); PrintType2(func_ptr);
    }

    void testQualifiers()
    {
        std::cout << "\n----------------" << std::endl;
        std::cout << "函数修饰符推导" << std::endl;
        const int tmp_a = 1;
        const int& tmp_b = tmp_a; // int&
        int&& tmp_c = 1;
        
        // auto推导不带限定符和引用，需要手动添加
        auto a = tmp_a; // int
        auto b = tmp_b; // int
        auto c = tmp_c; // int
        const auto auto_a = tmp_a; // const int
        const auto& auto_b = tmp_b; // const int&
        auto&& auto_c = tmp_c; // int&&
        PrintType2(tmp_a); PrintType2(a); PrintType2(auto_a);
        std::cout << std::endl;
        PrintType2(tmp_b); PrintType2(b); PrintType2(auto_b);
        std::cout << std::endl;
        PrintType2(tmp_c); PrintType2(c); PrintType2(auto_c);
    }

private:
    int func(int a, const int& b, int* c) { return 0; }
    // int func(int a) { return 0; } // auto无法推导重载函数
};

// 注册反射函数
_REGISTER(autoTest,
    &autoTest::testBaseType,
    &autoTest::testContainer,
    &autoTest::testLambda,
    &autoTest::testQualifiers
)

class DecltypeTest
{
public:
    void testReference()
    {
        std::cout << "----------------" << std::endl;
        std::cout << "decltype推导" << std::endl;
        int a = 1;
        decltype(a) b = a; // int
        decltype((a)) c = a; // int&，括号表达式为左值
        decltype((a + 1)) d = a; // int&，括号内为什么运算式，计算后为右值，decltype推导右值类型为什么实际类型

        PrintType2(b); PrintType2(c); PrintType2(d);
    }

    void testLambda()
    {
        const int a = 1;
        auto lambda1 = [](const int a, const int b) { const int& c = a; return c; };
        auto lambda2 = [&]() -> decltype(auto) { const int& c = a; return c; }; // 为了避免ub，a写在外面
        // 返回值是右值，返回类型是const int，decltype(lambda3(1, 2))推导时右值去掉const
        auto lambda3 = [](const int a, const int b) -> decltype(auto) { const int c = a; return c; }; 

        decltype(lambda1(1, 2))  retur1 = lambda1(1, 2);    // int
        decltype(lambda2())  retur2 = lambda2();            // const int&
        decltype(lambda3(1, 2))  retur3 = lambda3(1, 2);    // int

        PrintType2(retur1); PrintType2(retur2); PrintType2(retur3);
    }
};



_REGISTER(DecltypeTest,
    &DecltypeTest::testReference,
    &DecltypeTest::testLambda
)

#undef PrintType