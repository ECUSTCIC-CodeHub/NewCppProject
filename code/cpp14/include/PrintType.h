#pragma once

#include <iostream>
#include <iomanip>
#include <string>

// cpp规范的实现，各编译器实现不同，gcc和clang的实现没法看，msvc的正常
// gcc：
// type of  a : St16initializer_listIiE
// msvc：
// type of  a : class std::initializer_list<int>
#define PrintType(type) \
    std::cout << "type of "<<std::setw(6) << #type << " : " << typeid(type).name() << std::endl;

// 使用编译器扩展实现
// 跨平台差异基本没有，可以打印出限定符，命名空间等
template<typename T>
std::string getTypeName()
{
#ifdef _MSC_VER
    std::string func_sig = __FUNCSIG__; // 限定MSVC
    // 查找 "getTypeName<" 和 ">" 之间的部分
    const std::string prefix = "getTypeName<";
    const std::string suffix = ">(";
#else // GCC和Clang
    std::string func_sig = __PRETTY_FUNCTION__; // 限定GCC和clang
    const std::string prefix = "getTypeName() [with T = ";
    const std::string suffix = ";";
#endif

    size_t start = func_sig.find(prefix) + prefix.length();
    size_t end = func_sig.rfind(suffix);

    if (start == std::string::npos || end == std::string::npos)
    {
        return typeid(T).name();
    }
    return func_sig.substr(start, end - start);
}

#define PrintType2(type) \
    std::cout << "type of "<<std::setw(6) << #type << " : " << getTypeName<decltype(type)>() << std::endl;