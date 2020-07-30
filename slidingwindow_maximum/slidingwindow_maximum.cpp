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
/*
链接：https://www.nowcoder.com/questionTerminal/1624bc35a45c42c0bc17d17fa0cba788?answerType=1&f=discussion
来源：牛客网

方法一种存在很多大量重复计算，比如说，对于数组，假设我们当前遍历到下标i，对于下标i+1的元素（假设i和i+1都在同一个窗口），如果比arr[i]大，说明了什么？
如果arr[i+1] 已经大于了 arr[i], 那么还要arr[i]有什么用.就有点“既生瑜何生亮”的感觉。
如果arr[i+1] < arr[i]呢？显然arr[i]还是需要保留的。为什么呢？
因为又可以arr[i] 对于下一个arr[i+1]所在的窗口来说，arr[i]已经失效了。

假设这里有那么一个容器可以保留上述操作。

遍历数组的每一个元素，
如果容器为空，则直接将当前元素加入到容器中。
如果容器不为空，则让当前元素和容器的最后一个元素比较，如果大于，则将容器的最后一个元素删除，然后继续讲当前元素和容器的最后一个元素比较
如果当前元素小于容器的最后一个元素，则直接将当前元素加入到容器的末尾
如果容器头部的元素已经不属于当前窗口的边界，则应该将头部元素删除
总结一下，首先容器中放的元素应该是单调递减的。然后还有删除容器头部元素和最后一个元素的操作。因此，这样的数据结构就是双端队列。c++中就是deque
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