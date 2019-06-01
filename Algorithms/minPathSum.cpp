/* g++ -std=c++17 minPathSum.cpp -o minPathSum */
#include <iostream>
#include <vector>

struct TestSet
{
    std::vector<std::vector<int>> grid;
    int solution;
};

/**
 * minPathSum
 * 
 * Given a M x N grid filled with non-negative numbers, find a path 
 * from top left to bottom right which minimizes the sum of all numbers 
 * along its path. You can only move either down or right at any point in time.
 * Complexity: O(MN)
 * 
 * @param grid 2-D grid of non-negative numbers
 * @return The minimal path sum
 */
int minPathSum(std::vector<std::vector<int>> &grid)
{
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();
    // Base cases
    int pathSum = 0;
    
    // one row, so sum the row
    if (rows == 1)
    {
        for (int &k : grid[0])
        {
            pathSum += k;
        }
        return pathSum;
    }
    // one column, so sum the column
    if (cols == 1)
    {
        for (std::vector<int> &col : grid)
        {
            pathSum += col[0];
        }
        return pathSum;
    }
    
    // Tabulation:
    // solution[i][j] represents the value of the minimal
    // sum path to cell (i,j)
    int solutions[rows][cols];
    solutions[0][0] = grid[0][0];

    // Initialize top and left border cells.
    // There will always be only one path to each of these cells,
    //  - The sum with all the cells to the left, for top border,
    //  - The sum with all the cells above, for the left border
    for (int i = 1; i < rows; ++i)
    {
        solutions[i][0] = solutions[i-1][0] + grid[i][0];
    }
    for (int i = 1; i < cols; ++i)
    {
        solutions[0][i] = solutions[0][i-1] + grid[0][i];
    }
    
    // Fill in the solutions table bottom-up
    for (int x = 1; x < rows; ++x)
    {
        for (int y = 1; y < cols; ++y)
        {
            // Take the minimum path between the cell above
            // and the cell to the left of cell (x,y) to be
            // the better of the two paths.
            int betterPath = solutions[x-1][y];
            if (betterPath > solutions[x][y-1])
            {
                betterPath = solutions[x][y-1];
            }
            solutions[x][y] = betterPath + grid[x][y];
        }
    }

    return solutions[rows-1][cols-1];
}

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