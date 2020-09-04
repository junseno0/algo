#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
120. Triangle

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/triangle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*逆向思维*/
class Solution {
private:
    int mintriangle(vector<vector<int>>& triangle, std::vector<std::vector<int>>& memo, int row, int col) {
        if(row == triangle.size()) return 0;
        if(memo[row][col] != -1) return memo[row][col];
        memo[row][col] = std::min(mintriangle(triangle, memo, row+1, col+1), mintriangle(triangle, memo, row+1, col)) + triangle[row][col];
        return memo[row][col];
    }
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size() <= 0) return 0; 
        std::vector<std::vector<int>> memo(triangle.size()+1, vector<int>(triangle.size()+1, -1));
        return mintriangle(triangle, memo, 0, 0);
    }
};

/*DP solution*/
class Solution_DP {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size() <= 0) return 0; 
        for(int i = triangle.size()-2; i >= 0; i-- ) {
            for(int j = 0; j <= i; j++) {
                triangle[i][j] += std::min(triangle[i+1][j], triangle[i+1][j+1]);
            }
        }
        return triangle[0][0];
    }
};

int main() {

    Solution_DP sl;
    std::vector<std::vector<int>> vt = {{2}, {3,4}, {6, 5, 7}, {4, 1, 8, 3}};//min : 11
    int min = sl.minimumTotal(vt);
    std::cout<<"minmum for vt triangle is "<<min<<"\n";
    return 0;
}