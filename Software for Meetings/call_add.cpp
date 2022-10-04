/**
 * @file call_add.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstate calling a function in another file
 * @version 1.0.0
 * @date 2022-10-04
 * 
 * 
 */

#include "add.h"
#include <iostream>

int main()
{
    std::cout << add(5, 7) << '\n';
}