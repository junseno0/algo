#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
279. Perfect Squares

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:

Input: n = 12
Output: 3 
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/perfect-squares
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
* 原来犯错的地方在于，本来已经写出了转移方程，却写成了暴力枚举，明显代码的框架不是动态规划，这是需要看出来的。
*/
class Solution {
public:
    int numSquares(int n) {
        vector<int> memo(n+1, 0);
        memo[1] = 1;
        memo[0] = 0;
        for(int i = 1; i <= n; i++) {
            memo[i] = i;
            for(int j = 1; j * j <= i; j++) {
                memo[i] = std::min(memo[i - j * j] + 1, memo[i]);
            }
        }
        return memo[n];
    }
};

int main() {
    Solution sl;
    int min = sl.numSquares(12);
    std::cout<<"minPathSum is "<<min<<"\n";
    return 0;
}