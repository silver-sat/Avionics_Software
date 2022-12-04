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

    /**
     * @brief C-style loop
     *
     */

    int array1[5] = {4, 7, 2, 5, 1};
    size_t length = sizeof(array1) / sizeof(array1[0]);
    int sum1 = 0;

    for (size_t i = 0; i < length; i++)
    {
        sum1 += array1[i];
    }

    printf("Sum 1 is: %d\n", sum1); 

    /**
     * @brief for-each loop
     *
     */

    int array2[]{4, 7, 2, 5, 1};
    int sum2{0};

    for (int number : array2)
    {
        sum2 += number;
    }

    std::cout << "Sum 2 is: " << sum2 << '\n';

    /**
     * @brief Library function
     *
     */

    std::array array3 {4, 7, 2, 5, 1};
    std::cout << "Sum 3 is: " << std::accumulate(array3.begin(), array3.end(), 0) << '\n';
}