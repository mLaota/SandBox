// Compile with "g++ -std=c++17 -Wall variadicSum.cpp  -o variadicSum"
// Construct a solution that takes a variable number of rational arguments and computes the sum

#include <iostream>

// base case
template<typename T>
T sumR(T num)
{
    return num;
}

// recursive case
template<typename T, typename ... Args>
auto sumR(T first, Args ... rest)
{
    return first + sumR(rest ...);
}

int main()
{
    auto sum = sumR(2, 4.5, 5, 8, 9);
    std::cout << "the sum is " << sum << std::endl;
}
