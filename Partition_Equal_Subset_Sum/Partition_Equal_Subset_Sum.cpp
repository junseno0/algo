#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
416. Partition Equal Subset Sum

Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Note:

Each of the array element will not exceed 100.
The array size will not exceed 200.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/partition-equal-subset-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
* 解题过程中犯的错误包括忽略记忆化搜索，容器大小，总和除以2.
*/
class Solution_recursion {
private:
    std::vector<std::vector<int>> memo;
    bool canPartition(std::vector<int>& nums, int n, int sum) {
        if(sum == 0) return true;
        if(sum < 0 || n >= nums.size()) return false;
        if(memo[n][sum] != -1)
            return memo[n][sum];
        memo[n][sum] = canPartition(nums, n+1, sum) || canPartition(nums, n+1, sum-nums[n]);
        return memo[n][sum];
    }
public:
    bool canPartition(std::vector<int>& nums) {
        int m = nums.size();
        if(m < 1) return 0;
        int sum = 0;
        for(int i = 0; i < m; i++) {
            sum += nums[i];
        }
        if(sum & 1) return false;
        sum /= 2;
        memo = std::vector<std::vector<int>>(m+1, vector<int>(sum+1, -1));
        return canPartition(nums, 0, sum);
    }
};

/*
//DFS
class Solution(object):
    def canPartition(self, nums):
        if not nums: return True
        total = sum(nums)
        if total & 1:  # 和为奇数
            return False
        total = total >> 1  # 除2
        nums.sort(reverse=True)  # 逆排序
        if total < nums[0]:  # 当数组最大值超过总和的一半
            return False
        return self.dfs(nums, total)

    def dfs(self, nums, total):
        if total == 0:
            return True
        if total < 0:
            return False
        for i in range(len(nums)):
            if self.dfs(nums[i+1:], total - nums[i]):  # 除去i及其之前，保证每个数只用一次
                return True
        return False

作者：PennX
链接：https://leetcode-cn.com/problems/partition-equal-subset-sum/solution/dfs-chao-jian-dan-de-jian-zhi-xing-neng-ti-gao-25b/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

/*
// 动态规划方法
bool canPartition(vector<int>& nums) {
    int sum = 0, n = nums.size();
    for (int num : nums) sum += num;
    if (sum % 2 != 0) return false;
    sum = sum / 2;
    vector<bool> dp(sum + 1, false);
    // base case
    dp[0] = true;

    for (int i = 0; i < n; i++) 
        for (int j = sum; j >= 0; j--) 
            if (j - nums[i] >= 0) 
                dp[j] = dp[j] || dp[j - nums[i]];

    return dp[sum];
}

作者：labuladong
链接：https://leetcode-cn.com/problems/partition-equal-subset-sum/solution/0-1-bei-bao-wen-ti-bian-ti-zhi-zi-ji-fen-ge-by-lab/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

class Solution_DP_v1 {
public:
    bool canPartition(vector<int>& nums) {
        int m = nums.size();
        if(m < 1) return 0;
        int sum = 0;
        for(int i = 0; i < m; i++) {
            sum += nums[i];
        }
        if(sum & 1) return false;
        //dp
        //state: f(n), n indicates a val/sum
        //transfer func: f(n, sum) = f(n-1, sum) || f(n-1, sum-w(n))
        sum /= 2;
        vector<vector<bool>> dp(sum+1, vector<bool>(m, false));
        std::sort(nums.begin(), nums.end());
        if(nums.back() > sum) return false;
        //when k = 0, nums[0] is picked
        dp[nums[0]][0] = true;
        for(int val = 1; val <= sum; val++) {
            for(int k = 1; k < m; k++) {
                if(val-nums[k] >= 0)
                    dp[val][k] = dp[val][k-1] || dp[val-nums[k]][k-1];
                else
                    dp[val][k] = dp[val][k-1];
            }
        }

        //return
        return dp[sum][m-1];
    }
};

/*唯一需要注意的是 val 应该从后往前反向遍历，因为每个物品（或者说数字）只能用一次，以免之前的结果影响其他的结果。*/
class Solution_DP_v2 {
public:
    bool canPartition(vector<int>& nums) {
        int m = nums.size();
        if(m < 1) return 0;
        int sum = 0;
        for(int i = 0; i < m; i++) {
            sum += nums[i];
        }
        if(sum & 1) return false;
        //dp
        //state: f(n), n indicates a val/sum
        //transfer func: f(n, sum) = f(n-1, sum) || f(n-1, sum-w(n))
        sum /= 2;
        vector<bool> dp(sum+1, false);
        dp[0] = true;
        for(int k = 0; k < m; k++) {
            for(int val = sum; val > 0; val--) {
                if(val-nums[k] >= 0)
                    dp[val] = dp[val] || dp[val-nums[k]];
            }
        }

        //return
        return dp[sum];
    }
};

int main() {
    Solution_recursion sl;
    //std::vector<int> vt = {1, 5, 11, 5};//true
    std::vector<int> vt = {1, 5, 11, 3};//false
    int flag = sl.canPartition(vt);
    std::cout<<"canPartition ? : "<<flag<<"\n";
    return 0;
}