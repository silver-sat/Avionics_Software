/**
 * @file forward_declaration.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate forward declaration
 * @version 1.0.0
 * @date 2022-10-04
 * 
 * 
 */
#include <iostream>

int add(int a, int b);

int main(){
    int x{5};
    int y{7};
    std::cout << add(x, y) << '\n';
}

int add(int a, int b){
    return a + b;
}