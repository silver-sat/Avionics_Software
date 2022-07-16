#include <iostream>
#include <vector>

class Calculator
{
public:
    using number_type = int; // this is a nested type alias

    std::vector<number_type> m_resultHistory{};

    number_type add(number_type a, number_type b)
    {
        auto result{ a + b };

        m_resultHistory.push_back(result);

        return result;
    }
};

int main()
{
    Calculator calculator;

    std::cout << calculator.add(3, 4) << '\n'; // 7
    std::cout << calculator.add(99, 24) << '\n'; // 123

    for (Calculator::number_type result : calculator.m_resultHistory)
    {
        std::cout << result << '\n';
    }

    return 0;
}