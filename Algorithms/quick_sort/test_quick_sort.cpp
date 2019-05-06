// g++ -std=c++17 -fopenmp test_quick_sort.cpp -o test
// Multithreaded template quick-sort test

#include "quick_sort_omp.h"
#include <iostream>
#include <vector>
#include <string>

template <typename T>
struct TestSet
{
    std::vector<T> args;
    std::vector<T> solution;
};

template <typename T>
bool testQuickSort(TestSet<T> testSet)
{
    int len = static_cast<int>(testSet.args.size());
    bool passed = true;
    quick_sort(testSet.args.data(), 0, len-1);
    for (int i = 0; i < len; i++)
    {
        passed &= (testSet.args[i] == testSet.solution[i]);
    }
    if (!passed)
    {
        std::cout << "Expected {";
        for (T item : testSet.solution) { std::cout << item << " "; }
        std::cout << "}\nGot {";
        for (T item : testSet.args) { std::cout << item << " "; }
        std::cout << "}\n";
    }
    return passed;
}

int main()
{
    TestSet<int> set1;
    set1.args = {3, 2, 5, 4, 3, 0, 10};
    set1.solution = {0, 2, 3, 3, 4, 5, 10};

    TestSet<char> set2;
    set2.args = {'b', 'z', 'a', 'f', 'c', 'e'};
    set2.solution = {'a', 'b', 'c', 'e', 'f', 'z'};
 
    TestSet<std::string> set3;
    set3.args = {"Apple", "apple", "zBanana", "banana", "Banana"};
    set3.solution = {"Apple", "Banana", "apple", "banana", "zBanana"};

    if (testQuickSort(set1) && testQuickSort(set2) && testQuickSort(set3))
    {
        std::cout << "Test passed\n";
    }
    else
    {
        std::cout << "Test failed\n";
    }
    return 0;
}
