/* g++ -std=c++17 minPathSum.cpp -o minPathSum */
#include <iostream>
#include "minPathSum.h"

struct TestSet
{
    std::vector<std::vector<int>> grid;
    int solution;
};

int main()
{
    std::vector<TestSet> tests(6);
    
    // Standard grid
    tests[0].grid =
    {
       {1, 3, 1},
       {1, 5, 1},
       {4, 2, 1}
    };
    tests[0].solution = 7;

    // More columns than rows
    tests[1].grid =
    {
       {1, 2, 5},
       {3, 2, 1}
    };
    tests[1].solution = 6;

    // More rows than columns
    tests[2].grid =
    {
        {1, 2},
        {3, 2},
        {4, 6}
    };
    tests[2].solution = 11;

    // One row
    TestSet test4;
    tests[3].grid =
    {
        {1, 5, 2}
    };
    tests[3].solution = 8;

    // One column
    tests[4].grid =
    {
        {3},
        {4},
        {50}
    };
    tests[4].solution = 57;

    // One cell
    tests[5].grid =
    {
        {29}
    };
    tests[5].solution = 29;

    for (int i = 0; i < (int)tests.size(); ++i)
    {
        std::cout << "Test " << i << ": ";
        if (minPathSum(tests[i].grid) == tests[i].solution)
        {
            std::cout << "Passed" << std::endl;
        }
        else
        {
            std::cout << "Failed" << std::endl;
            break;
        }
    }

    return 0;
}