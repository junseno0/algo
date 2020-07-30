#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

/*
Given an array nums, there is a sliding window of size k which is moving from the very
left of the array to the very right. You can only see the k numbers in the window.
Each time the sliding window moves right by one position. Return the max sliding window.
给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。
*/

/*
Solution:
https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/solution/mian-shi-ti-59-i-hua-dong-chuang-kou-de-zui-da-1-6/
*/
class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
        std::vector<int> ret;
        std::deque<int> dq;
        int index = 0;//if index = k-1; window got.
        int removeindex = 0;
        if(nums.size() == 0)
            return ret;
        //put first k element to deque
        while(index < k) {
            while(dq.size() > 0 && nums[index] >= dq.back()) {
                dq.pop_back();
            }
            dq.push_back(nums[index]);
            index++;
        }
        ret.push_back(dq.front());//first maximum

        //put element to deque
        //delete those elements smaller and then insert
        //if element smaller than deque back, push_back it

        //if deleting element is the deque front, pop front one ahead of putting element
        while(index < nums.size()) {
            if(nums[removeindex] == dq.front()) {
                dq.pop_front();
            }
            while(dq.size() > 0 && nums[index] > dq.back()) {
                dq.pop_back();
            }
            dq.push_back(nums[index]);
            ret.push_back(dq.front());
            index++;
            removeindex++;
        }

        //deque front is the maximum, put it to a vector when window got

        //return vector ret
        return ret;
    }
};

int main() {
    //Solution sl;
    Solution sl;
    std::vector<int> ret;
    std::vector<int> vt1 = {2, 1};
    std::vector<int> vt2 = {5, -1, 5, 4, 3};
    std::vector<int> vt3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ret = sl.maxSlidingWindow(vt1, 1);
    std::cout<<"sl maxSlidingWindow: \n";
    for(auto it : ret) std::cout<<"["<<it<<"] ";
    std::cout<<"\n";

    ret = sl.maxSlidingWindow(vt2, 2);
    std::cout<<"sl maxSlidingWindow: \n";
    for(auto it : ret) std::cout<<"["<<it<<"] ";
    std::cout<<"\n";

    ret = sl.maxSlidingWindow(vt3, 3);
    std::cout<<"sl maxSlidingWindow: \n";
    for(auto it : ret) std::cout<<"["<<it<<"] ";
    std::cout<<"\n";
    return 0;
}