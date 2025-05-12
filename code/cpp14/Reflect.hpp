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

// 辅助函数：递归调用元组中的所有函数指针
template<typename T, typename Tuple, std::size_t... Index>
void invokeFunctions(T& instance, Tuple& funcs, std::index_sequence<Index...>)
{
    // 通过展开参数包递归调用
    auto dummy = { ((instance.*std::get<Index>(funcs))(), 0)... };
    (void)dummy;
}

// 反射函数，自动调用注册的所有函数
template<typename T>
void TestClass() 
{
    T instance{};
    constexpr auto& funcs = FunctionInfo<T>::list;
    constexpr auto size = std::tuple_size<std::remove_reference_t<decltype(funcs)>>::value;
    invokeFunctions(instance, funcs, std::make_index_sequence<size>{});
    std::cout << std::endl;
}

// 注册宏，注册的函数会被反射函数调用
// 使用模板特化实现
#define _REGISTER(classname, ...) \
    template<> \
    struct FunctionInfo<classname> { \
        static constexpr auto list = std::make_tuple(__VA_ARGS__); \
    };
