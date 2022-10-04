/**
 * @file print_input.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate getting and printing user input
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

void print_output(int value){
    std::cout << "You typed: " << value << '\n';
}

int main(){
    print_output(get_input());
}