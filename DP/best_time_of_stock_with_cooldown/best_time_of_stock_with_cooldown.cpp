#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
309. Best Time to Buy and Sell Stock with Cooldown

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

Input: [1,2,3,0,2]
Output: 3 
Explanation: transactions = [buy, sell, cooldown, buy, sell]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
第一步：状态定义
dp[i][j] 表示 [0, i] 区间内，在下标为 i 这一天状态为 j 时的最大收益。

这里 j 取三个值：

0 表示不持股；
1 表示持股；
2 表示处在冷冻期。

第二步：状态转移方程
不持股可以由这两个状态转换而来：
昨天不持股，今天什么都不操作，仍然不持股；
昨天持股，今天卖了一股。
持股可以由这两个状态转换而来：
昨天持股，今天什么都不操作，仍然持股；
昨天处在冷冻期，今天买了一股；
处在冷冻期只可以由不持股转换而来，因为题目中说，刚刚把股票卖了，需要冷冻 1 天。

作者：liweiwei1419
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/solution/dong-tai-gui-hua-by-liweiwei1419-5/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n < 2) return 0;
        //dp
        vector<vector<int>> dp(2, vector<int>(3,0));
        //not got: 0 got: 1 frozen: 2

        //not got <-- not got / got
        // got <-- got / frozen
        //frozen <-- not got 
        
        //init 
        dp[0][1] = -prices[0];

        //from day1 , day2, ..., day n-1
        //由于当前天只参考了昨天的状态值，因此可以考虑使用「滚动数组」
        for(int i = 1; i < n; i++) {
            dp[i&1][0] = std::max(dp[(i-1)&1][0], prices[i]+dp[(i-1)&1][1]);
            dp[i&1][1] = std::max(dp[(i-1)&1][1], dp[(i-1)&1][2]-prices[i]);
            dp[i&1][2] = dp[(i-1)&1][0];
        }

        //return
        return std::max(dp[(n-1)&1][0], dp[(n-1)&1][2]);
    }
};

int main() {
    Solution sl;
    std::vector<int> vt = {1,2,3,0,2};
    int max = sl.maxProfit(vt);
    std::cout<<"maxProfit is "<<max<<"\n";
    return 0;
}