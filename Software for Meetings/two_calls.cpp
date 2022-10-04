/**
 * @file two_calls.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate nested function calls
 * @version 1.0.0
 * @date 2022-10-04
 *
 *
 */
#include <iostream>

void function_b()
{
    std::cout << "In function_b\n";
}

void function_a()
{
    std::cout << "In function_a\n";
    function_b();
}

int main()
{
    std::cout << "Starting main\n";
    function_a();
    std::cout << "Ending main\n";
}