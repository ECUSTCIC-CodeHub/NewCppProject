#pragma once

#include <tuple>
#include <utility>
#include <ostream>
#include <iostream>

// 基本模板类，保存调用函数信息
template<typename T>
struct FunctionInfo
{
    static constexpr auto list = std::make_tuple();
};

// 反射函数，自动调用注册的所有函数
template<typename T>
void TestClass() 
{
    T instance{};
    // std::apply将元组中的所有值作为参数传递给函数
    // 函数调用使用了折叠表达式
    std::apply([&](auto&&... funcs) 
        {
        ((instance.*funcs)(), ...);
        },
        FunctionInfo<T>::list);
    std::cout << std::endl;
}

// 注册宏，注册的函数会被反射函数调用
// 使用模板特化实现
#define _REGISTER(classname, ...) \
    template<> \
    struct FunctionInfo<classname> { \
        static constexpr auto list = std::make_tuple(__VA_ARGS__); \
    };
