#include "Deduction.hpp"  
#include <iostream>  
#include "Reflect.hpp"  


int func()
{
    return 1;
}

auto a = { (func(), 0) };

int main()  
{  
   system("chcp 65001");  
  
   std::cout << *a.begin();
   TestClass<autoTest>();  
   TestClass<DecltypeTest>();  
}