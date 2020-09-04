#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>
#include <unordered_set>
using namespace std;

/*
15. 3Sum
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/*
* 1，第一想法，采用哈希，但是去重确实麻烦
* 2，提醒之下，采用双指针，固定某一位，左右各一指针向中间移动，想不出去重的完整方案，出现某种情况难以处理
* 3，通过将左右指针安排在固定位的右方，可以解决原始方案的去重难点。新的思路可以更流畅地解决问题。
*/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        //check
        std::vector<std::vector<int>> res;
        res.clear();
        if(nums.size() < 3) return res;
        //k from 0 to size - 3
        //left from k+1, right from size-1
        //if left move, skip same, if right move, skip same
        //if k move, skip same
        std::sort(nums.begin(), nums.end());
        for(int k = 0; k < nums.size()-2; k++) {
            if(nums[k] > 0) return res;
            if(k > 0 && nums[k] == nums[k-1]) continue;//It's IF, NOT while
            int left = k + 1;
            int right = nums.size()-1;
            while(left < right) {
                int sum = nums[k] + nums[left] + nums[right];
                if(sum < 0) {
                    left++;
                    while(left < right && nums[left] == nums[left-1]) left++; 
                } else if (sum > 0) {
                    right--;
                    while(left < right && nums[right] == nums[right+1]) right--;
                } else {
                    res.push_back({nums[k], nums[left], nums[right]});
                    left++;
                    right--;
                    while(left < right && nums[left] == nums[left-1]) left++;//required!
                    while(left < right && nums[right] == nums[right+1]) right--;//required!
                }
            }
        }

        //return
        return res;
    }
};

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