#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
62. Unique Paths

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-paths
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
* 未考虑清楚边界的赋值。
*/
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        //dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + w[i][j]
        int m = obstacleGrid.size();
        if(m <= 0) return 0;
        int n = obstacleGrid[0].size();
        vector<vector<int>> memo(m, vector<int>(n, 0));
        memo[0][0] = !obstacleGrid[0][0];//trick
        for(int i = 0; i < n &&  obstacleGrid[0][i] == 0; i++)//trick
            memo[0][i] = 1;
        for(int i = 0; i < m && obstacleGrid[i][0] == 0; i++)//trick
            memo[i][0] = 1;
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                if(obstacleGrid[i][j] == 0)
                    memo[i][j] = memo[i-1][j] + memo[i][j-1];
            }
        }
        return memo[m-1][n-1];
    }
};


int main() {
    Solution sl;
    std::vector<std::vector<int>> vt{{0,0},{1,1},{0,0}};//0
    int count = sl.uniquePathsWithObstacles(vt);
    std::cout<<"uniquePathsWithObstacles is "<<count<<"\n";
    return 0;
}