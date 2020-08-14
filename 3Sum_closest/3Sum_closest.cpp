#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>
#include <unordered_set>
using namespace std;

/*
16. 3Sum Closest
Given an array nums of n integers and an integer target, find three integers
in nums such that the sum is closest to target. Return the sum of the three integers.
You may assume that each input would have exactly one solution.

Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum-closest
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
* 1，未考虑整型溢出，但凡相加与相减，都可能溢出。
*/

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        //check
        int res = INT_MAX;
        if(nums.size() < 3) return res;
        //k from 0 to size - 3
        //left from k+1, right from size-1
        //if left move, skip same, if right move, skip same
        //if k move, skip same
        std::sort(nums.begin(), nums.end());
        for(int k = 0; k < nums.size()-2; k++) {
            if(k > 0 && nums[k] == nums[k-1]) continue;//It's IF, NOT while
            int left = k + 1;
            int right = nums.size()-1;
            while(left < right) {
                int sum = nums[k] + nums[left] + nums[right];
                if(sum < target) {
                    if((long)abs((long)target-(long)sum)<abs((long)target-(long)res)) res = sum;
                    left++;
                    while(left < right && nums[left] == nums[left-1]) left++; 
                } else if (sum > target) {
                    if((long)abs((long)target-(long)sum)<(long)abs((long)target-(long)res)) res = sum;
                    right--;
                    while(left < right && nums[right] == nums[right+1]) right--;
                } else {
                    return target;
                }
            }
        }

        //return
        return res;
    }
};
/*
//可以采用lambda表达式作最优判断。
auto update = [&](int cur) {
            if (abs(cur - target) < abs(best - target)) {
                best = cur;
            }
        };
*/

int main() {
    Solution sl;
    std::vector<int> vt= {-1, 0, 1, 2, -1, -4};
    std::vector<std::vector<int>> res = sl.threeSum(vt);
    for(auto itt : res) {
        for(auto it : itt)
            std::cout<<"["<<it<<"] ";
        std::cout<<"\n";
    }
    return 0;
}