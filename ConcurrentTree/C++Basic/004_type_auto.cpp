#include <iostream>
#include <stdio.h>

int main(void)
{
    int a = 10;
    int b(a); //
    auto c(b);

    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << a + c + b << std::endl;

    return 0;
}