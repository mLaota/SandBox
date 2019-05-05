// compile using "g++ -std=c++17 -Wall test_stable_marriage.cpp -o test_stable_marriage"

#include <iostream>
#include <stdio.h>
#include "stable_marriage.h"
#include <set>
#include <algorithm>

typedef struct TestSet
{
    vector<vector<int>> men_prefs;
    vector<vector<int>> women_prefs;
    vector<int> solution;
} TestSet;

bool testStableMarriage(TestSet& testSet)
{
    bool ret = false;
    do
    {
        // Assign aliases
        std::vector<vector<int>>& men_prefs = testSet.men_prefs;
        std::vector<vector<int>>& women_prefs = testSet.women_prefs;
        
        // Test that there are N men and N women
        int N = static_cast<int>(men_prefs.size());
        if (N != static_cast<int>(women_prefs.size()))
        {
            std::cout << "Error: Stable marriage requires the number of men to "
                         "be equal to the number of women" << std::endl;
            break;
        }
        
        // Test that the preference lists are well-formed. A well-formed 
        // preference lists contains N unique integers        
        bool wellFormedPreferenceLists = true;
        std::set<int> uniqueContainer;
        
        // Set flag to false if a non-unique value is given
        auto checkUnique = [&wellFormedPreferenceLists, &uniqueContainer] (int val)
        {
            wellFormedPreferenceLists &= uniqueContainer.insert(val).second;
        };

        for (auto prefs : men_prefs)
        {
            uniqueContainer.clear();
            std::for_each(prefs.begin(), prefs.end(), checkUnique);
        }
        for (auto prefs : women_prefs)
        {
            uniqueContainer.clear();
            std::for_each(prefs.begin(), prefs.end(), checkUnique);
        }

        if (!wellFormedPreferenceLists)
        {
            std::cout << "Error: Each preference list must have " << N
                      << " unique integers" << std::endl;
            break;
        }

        // Run the algorithm 
        vector<int> matches = stable_marriage(N, men_prefs, women_prefs);
        
        bool pass = true;
        for (auto i = 0; i < N; i++)
        {
            pass = (matches[i] == testSet.solution[i]);
            if (!pass)
            {
                printf("Value i=%d mismatch (%d != %d)\n", i, matches[i], testSet.solution[i]);
                break;
            }
        }
        ret = pass;
    } while (0);
    return ret;
}

int main()
{
    std::vector<TestSet> tests;
    
    // Set 1
    TestSet set1;

    set1.men_prefs = 
    {
        {2, 1},
        {1, 2}
    };

    set1.women_prefs =
    {
        {1, 2},
        {2, 1}
    };
    
    set1.solution = {2, 1};
    
    tests.emplace_back(set1);
    
    // Set 2
    TestSet set2;
    
    set2.men_prefs = 
    {
        {8, 3, 7, 1, 4, 2, 5, 10, 6, 9},
        {7, 4, 8, 3, 9, 6, 2, 1, 5, 10},
        {8, 6, 10, 4, 7, 1, 3, 9, 5, 2},
        {2, 1, 8, 6, 3, 9, 5, 4, 7, 10},
        {2, 3, 7, 5, 4, 6, 9, 10, 1, 8},
        {9, 8, 7, 10, 5, 6, 1, 2, 3, 4},
        {10, 4, 6, 9, 7, 1, 8, 3, 5, 2},
        {8, 1, 4, 3, 10, 7, 9, 5, 2, 6},
        {2, 4, 5, 10, 9, 3, 6, 1, 8, 7},
        {6, 8, 1, 9, 4, 5, 10, 3, 7, 2}
    };

    set2.women_prefs =
    {
        {10, 3, 8, 5, 4, 9, 1, 7, 2, 6},
        {10, 6, 9, 7, 3, 4, 1, 5, 8, 2},
        {8, 4, 3, 10, 6, 1, 2, 5, 7, 9},
        {3, 10, 6, 2, 1, 5, 9, 4, 7, 8},
        {7, 2, 8, 9, 3, 1, 4, 10, 6, 5},
        {5, 4, 2, 6, 7, 8, 3, 9, 10, 1},
        {6, 1, 4, 2, 10, 9, 3, 7, 5, 8},
        {8, 7, 3, 5, 1, 10, 6, 4, 9, 2},
        {10, 8, 7, 6, 2, 1, 3, 4, 5, 9},
        {10, 7, 1, 3, 4, 8, 6, 9, 2, 5}
    };
    
    set2.solution = {10, 9, 1, 3, 5, 4, 2, 8, 6, 7};

    tests.emplace_back(set2);
    
    // Set 3    
    TestSet set3;
     
    set3.men_prefs =
    {
        {10, 2, 1, 4, 6, 5, 7, 8, 9, 3},
        {8, 3, 7, 1, 4, 9, 2, 5, 6, 10},
        {7, 9, 3, 10, 1, 6, 5, 8, 2, 4},
        {5, 8, 7, 10, 4, 2, 3, 9, 1, 6},
        {3, 5, 10, 4, 6, 2, 7, 9, 1, 8},
        {3, 7, 8, 1, 10, 9, 6, 4, 5, 2},
        {6, 3, 10, 5, 2, 4, 9, 1, 8, 7},
        {8, 10, 7, 6, 3, 9, 1, 2, 5, 4},
        {4, 10, 7, 3, 5, 1, 2, 6, 9, 8},
        {9, 8, 1, 10, 4, 7, 6, 3, 2, 5}
    };

    set3.women_prefs =
    {
        {10, 2, 7, 9, 3, 5, 6, 4, 1, 8},
        {4, 2, 9, 1, 3, 5, 6, 10, 7, 8},
        {3, 5, 6, 10, 1, 2, 7, 4, 8, 9},
        {5, 1, 9, 3, 2, 10, 4, 7, 8, 6},
        {6, 9, 4, 10, 8, 5, 1, 2, 3, 7},
        {6, 5, 8, 10, 1, 7, 3, 4, 2, 9},
        {6, 4, 2, 1, 5, 7, 10, 3, 9, 8},
        {1, 6, 8, 3, 5, 10, 2, 7, 9, 4},
        {1, 3, 2, 8, 10, 5, 6, 7, 4, 9},
        {2, 4, 8, 6, 3, 7, 5, 9, 10, 1}
    };

    set3.solution = {10, 2, 5, 9, 4, 7, 6, 8, 3, 1};

    tests.emplace_back(set3);
    
    for (int i = 0; i < static_cast<int>(tests.size()); i++)
    {
        if (testStableMarriage(tests[i])) 
        {
            printf("Test %d: Pass\n", i+1); 
        }
        else 
        { 
            printf("Test %d: Failed. Exiting program\n", i+1); 
            break;
        }
    }

    return 0;
}
