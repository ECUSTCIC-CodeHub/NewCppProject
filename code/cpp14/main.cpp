#include "Deduction.hpp"
#include <iostream>
#include "Reflect.hpp"


int main()
{
    system("chcp 65001");

    TestClass<autoTest>();
    TestClass<DecltypeTest>();
}