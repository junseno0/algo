#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
64. Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example:

Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-path-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution_recursion_memo {
private:
    int m;
    int n;
    vector<vector<int>> memo;
    // Point(x, y) to Point(m-1, m-1) minmum path
    int minpath(vector<vector<int>>& grid, int x, int y) {
        //constraints.
        if(x == m-1 && y == n-1) return grid[m-1][n-1];
        if(x >= m || y >= n) return INT_MAX;
        if(memo[x][y] != -1)
            return memo[x][y];
        memo[x][y] = std::min(minpath(grid, x+1, y), minpath(grid, x, y+1)) + grid[x][y];
        return memo[x][y];
    }
public:
    int minPathSum(vector<vector<int>>& grid) {
        //check
        if(grid.size() <= 0) return 0;
        m = grid.size();
        n = grid[0].size();
        memo = vector<vector<int>>(m, vector<int>(n, -1));

        return minpath(grid, 0, 0);
    }
};

class Solution_DP_v1 {
private:
    int m;
    int n;
    //这里搞得太繁琐了，为什么要遍历行，遍历列，然后再遍历下一行，遍历下一列呢
    //未抓住本质，从坐标（1，1）开始，每个点都存在上边元素与左边元素，从左至右
    //从上到下遍历每个元素就可以了，不必要这么麻烦
    void minpath(vector<vector<int>>& grid, int x, int y) {
        if(x == m && y == n) return;

        for(int i = x; i < m; i++) {
            grid[i][y] += std::min(grid[i-1][y], grid[i][y-1]);//left and up one
        }
        //trick j = y+1
        for(int j = y+1; j < n; j++) {
            grid[x][j] += std::min(grid[x-1][j], grid[x][j-1]);
        }

    }
public:
    int minPathSum(vector<vector<int>>& grid) {
        //check
        if(grid.size() <= 0) return 0;
        m = grid.size();
        n = grid[0].size();
        //trick
        for(int i = 1; i < m; i++) {
            grid[i][0] += grid[i-1][0];
        }
        for(int i = 1; i < n; i++) {
            grid[0][i] += grid[0][i-1];
        }
        for(int i = 1, j = 1; i < m && j < n; i++, j++) {
            minpath(grid, i, j);
        }
        
        return grid[m-1][n-1];
    }
};

/*这是对上一个解法的优化*/
class Solution_DP_v2 {
public:
    int minPathSum(vector<vector<int>>& grid) {
        //check
        if(grid.size() <= 0) return 0;
        int m = grid.size();
        int n = grid[0].size();
        for(int i = 1; i < m; i++) {
            grid[i][0] += grid[i-1][0];
        }
        for(int i = 1; i < n; i++) {
            grid[0][i] += grid[0][i-1];
        }
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++)
                grid[i][j] += std::min(grid[i-1][j], grid[i][j-1]);
        }
        
        return grid[m-1][n-1];
    }
};

int main() {
    Solution_DP_v2 sl;
    std::vector<std::vector<int>> vt = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};//min : 7
    int min = sl.minPathSum(vt);
    std::cout<<"minPathSum is "<<min<<"\n";
    return 0;
}