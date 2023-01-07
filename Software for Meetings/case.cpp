#include <iostream>

int main()
{

    std::string a{"one"};
    switch ('y')
    {
    case 1:
    case 3:
        std::cout << "1 or 3";
        break;
    case 2:
    case 4:
        std::cout << "2 or 4";
        break;
    default:
        std::cout << "unexpected";
    }
}