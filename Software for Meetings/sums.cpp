/**
 * @file sums.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate multiple language "levels"
 * @version 1.0.0
 * @date 2022-12-04
 *
 *
 */

#include <iostream>
#include <array>
#include <numeric>

int main()
{

    // Traditional C-style loop

    constexpr size_t array_size{5};
    constexpr int array1[array_size] = {4, 7, 2, 5, 1};
    int sum1 = 0;

    for (size_t i = 0; i < array_size; i++)
    {
        sum1 = sum1 + array1[i];
    }

    printf("Sum 1 is: %d\n", sum1);

    // For-each loop (avoids off-by-one and indexing errors)

    constexpr int array2[]{4, 7, 2, 5, 1};
    int sum2{0};

    for (auto number : array2)
    {
        sum2 += number;
    }

    std::cout << "Sum 2 is: " << sum2 << '\n';

    // Library function (available in environments supporting the standard library)

    std::array array3{4, 7, 2, 5, 1};
    std::cout << "Sum 3 is: " << std::accumulate(array3.begin(), array3.end(), 0) << '\n';
}