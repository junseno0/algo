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

class Solution_DP_v1 {
public:
    int uniquePaths(int m, int n) {
        
        //dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + w[i][j]
        vector<vector<int>> memo(m, vector<int>(n, 1));
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                memo[i][j] = memo[i-1][j] + memo[i][j-1];
            }
        }
        return memo[m-1][n-1];
    }
};

class Solution_DP_v2 {
public:
    int uniquePaths(int m, int n) {
        
        //dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + w[i][j]
        vector<int> memo(n, 1);
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                memo[j] = memo[j] + memo[j-1];
            }
        }
        return memo[n-1];
    }
};

int main() {
    Solution_DP_v2 sl;
    int count = sl.uniquePaths(7, 3);//28
    std::cout<<"uniquePaths is "<<count<<"\n";
    return 0;
}