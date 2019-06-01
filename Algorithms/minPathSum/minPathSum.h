#include <vector>

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

    // Base cases...
    // one row, so sum the row
    if (rows == 1)
    {
        int pathSum = 0;
        for (int &k : grid[0])
        {
            pathSum += k;
        }
        return pathSum;
    }
    // one column, so sum the column
    if (cols == 1)
    {
        int pathSum = 0;
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