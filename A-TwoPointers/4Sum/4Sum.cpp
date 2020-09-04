#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>
#include <unordered_set>
using namespace std;

/*
18. 4Sum

Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

The solution set must not contain duplicate quadruplets.

Example:

Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/4sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。。
*/
/*
* 误以为不能用双指针方法，实际上，哈希是用不了的，双指针法扩展一下，不就可以了吗？
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        //check
        std::vector<std::vector<int>> res;
        res.clear();
        if(nums.size() < 4) return res;

        //k, j , left, right
        //k move to next diff one, from 0 to size-4
        //j move to next diff one, from k+1 to size-3
        //left from j+1, right from size-1
        //left move to next diff one, right same
        std::sort(nums.begin(), nums.end());
        for(int k = 0; k <= nums.size() - 4; k++) {
            if(k > 0 && nums[k] == nums[k-1]) continue;
            for(int j = k+1; j <= nums.size() - 3; j++) {
                int left = j+1;
                int right = nums.size()-1;
                if(j > k+1 && nums[j] == nums[j-1]) continue;
                while(left < right) {
                    int sum = nums[k] + nums[j] + nums[left] + nums[right];
                    if(sum < target) {
                        left++;
                        while(left < right && nums[left] == nums[left-1]) left++;
                    } else if(sum > target) {
                        right--;
                        while(left < right && nums[right] == nums[right+1]) right--;
                    } else {
                        res.push_back({nums[k], nums[j], nums[left], nums[right]});
                        left++;
                        right--;
                        while(left < right && nums[left] == nums[left-1]) left++;
                        while(left < right && nums[right] == nums[right+1]) right--;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    Solution sl;
    std::vector<int> vt= {1,0,-1,0,-2,2};
    std::vector<std::vector<int>> res = sl.fourSum(vt, 0/*target*/);
    for(auto itt : res) {
        for(auto it : itt)
            std::cout<<"["<<it<<"] ";
        std::cout<<"\n";
    }
    return 0;
}