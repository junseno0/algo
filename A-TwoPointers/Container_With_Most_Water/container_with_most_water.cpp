#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>
#include <unordered_set>
using namespace std;

/*
11. Container With Most Water
Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai).
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
Find two lines, which together with x-axis forms a container, such that the container contains the most water.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/container-with-most-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/*未能找出其中的不变性*/
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right= height.size()-1;
        int res = 0;
        while(left < right) {
            if(height[left] <= height[right]) {
                res = std::max(res, height[left] * (right - left));
                left++;
            } else {
                res = std::max(res, height[right] * (right - left));
                right--;
            }
        }
        return res;
    }
};

int main() {
    Solution sl;
    std::vector<int> vt= {1,8,6,2,5,4,8,3,7};//49
    int res = sl.maxArea(vt);
    std::cout<<"sl maxArea : "<<res<<" \n";
    return 0;
}