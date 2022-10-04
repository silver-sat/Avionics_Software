/**
 * @file get_input.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate function for user input
 * @version 1.0.0
 * @date 2022-10-04
 * 
 * 
 */
#include <iostream>

int get_input(){
    std::cout << "Enter an integer: ";
    int input_value{};
    std::cin >> input_value;
    return input_value;
}

int main(){
    auto input_value{get_input()};
    std::cout << "You typed: " << input_value << '\n';
}