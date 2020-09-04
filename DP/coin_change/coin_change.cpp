#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
322. Coin Change

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:

Input: coins = [1, 2, 5], amount = 11
Output: 3 
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/coin-change
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
思路：

看题目的问法，只问最优值是多少，没有要我们求最优解，一般情况下就是「动态规划」可以解决的问题；
最优子结构其实比较明显，根据示例 1：

输入: coins = [1, 2, 5], amount = 11
凑成面值为 11 的最小***数可以由以下 33 者的最小值得到：

1、凑成面值为 10 的最小数 + 面值为 1 的这一枚；

2、凑成面值为 9 的最小数 + 面值为 2 的这一枚；

3、凑成面值为 6 的最小数 + 面值为 5 的这一枚；

即 dp[11] = min (dp[10] + 1, dp[9] + 1, dp[6] + 1)。

可以直接把题目的问法设计成状态。

作者：liweiwei1419
链接：https://leetcode-cn.com/problems/coin-change/solution/dong-tai-gui-hua-shi-yong-wan-quan-bei-bao-wen-ti-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
class Solution_DP_v1 {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(coins.size() < 1 || amount <= 0) return 0;
        vector<int> dp(amount+1, amount+1);
        dp[0] = 0;
        std::sort(coins.begin(), coins.end());
        for(int val = 1; val <= amount; val++) {
            for(int i = 0; i < coins.size(); i++) { //coins[0], coins[1].... coins[coins.size()-1]
                if(val-coins[i] < 0) break;
                dp[val] = std::min(dp[val], 1 + dp[val-coins[i]]);
            }
        }
        if(dp[amount] > amount) return -1;
        return dp[amount];
    } 
};

/*
* 采用元素遍历的方式，添加限制判断进行剪枝
*/
class Solution_DP_v2 {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(coins.size() < 1 || amount <= 0) return 0;
        int count = 0;
        vector<int> dp(amount+1, amount+1);
        dp[0] = 0;
        std::sort(coins.begin(), coins.end());
        for(int val = 1; val <= amount; val++) {
            for(auto coin : coins) { //coins[0], coins[1].... coins[coins.size()-1]
                if(val - coin < 0) break;
                if (dp[val - coin] != amount + 1) {
                     dp[val] = std::min(dp[val], 1 + dp[val-coin]);
                }
            }
        }
        if(dp[amount] > amount) return -1;
        return dp[amount];
    } 
};

/*
在添加到队列的时候，就得将 visited 数组对应的值设置为 true，否则可能会出现同一个元素多次入队的情况。
*/
class Solution_BFS {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(coins.size() < 1 || amount <= 0) return 0;
        int count = 0;
        std::queue<int> qt;
        std::vector<bool> visited(amount+1, false);
        qt.push(0);
        std::sort(coins.begin(), coins.end());
        while(!qt.empty()) {
            int size = qt.size();
            count++;
            while(size--) {
                int val = qt.front();
                qt.pop();
                if(val > amount) continue;
                for(auto coin : coins) {
                    if(coin + val > amount) break;
                    if(coin + val == amount) return count;
                    if(visited[coin+val] == false) {
                        visited[coin+val] = true;
                        qt.push(coin+val);
                    }
                }
            }
        }
        return -1;
    } 
};

int main() {
    Solution_DP_v1 sl;
    std::vector<int> vt = {1, 2, 5};//false
    int mincount = sl.coinChange(vt, 11);
    std::cout<<"coinChange mincount : "<<mincount<<"\n";
    return 0;
}