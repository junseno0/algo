#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>
#include <unordered_set>
using namespace std;

/*
167. Two Sum II - Input array is sorted

Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

Note:

Your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution and you may not use the same element twice.
Example:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution_set {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        std::unordered_set<int> record;
        std::vector<int> ret;
        for(auto it : numbers)
            record.insert(it);
        for(int i = 0; i < numbers.size(); i++) {
            if(record.find(target-numbers[i]) != record.end()) {
                for(int j = i+1; j < numbers.size() && numbers[j]+numbers[i] <= target; j++) {
                    if(numbers[j] + numbers[i] == target)
                        return ret = {i+1, j+1};
                }
            }
        }
        return ret;
    }
};

class Solution_2_runner {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        std::vector<int> ret;
        int left = 0;
        int right = numbers.size()-1;
        while(left < right) {
            //if sum > target, move right
            //if sum < target, move left ahead
            if(numbers.at(left) + numbers.at(right) == target) {
                return ret = {left+1, right+1};
            } else if(numbers.at(left) + numbers.at(right) > target) {
                right--;
            } else {
                left++;
            }
        }
        return ret;
    }
};

int main() {
    Solution_2_runner sl;
    std::vector<int> vt = {2, 7, 11, 16};
    std::vector<int> res = sl.twoSum(vt, 13);
    std::cout<<"sl two sum position: \n";
    for(int i = 0; i < res.size(); i++)
        std::cout<<"["<<res.at(i)<<"] ";
    return 0;
}