#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
42. Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.


The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. 
In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!

Example:

Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/trapping-rain-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
* 直接按问题描述进行。对于数组中的每个元素，我们找出下雨后水能达到的最高位置，等于两边最大高度的较小值减去当前高度的值。
*/
/*
int trap(vector<int>& height)
{
    int ans = 0;
    int size = height.size();
    for (int i = 1; i < size - 1; i++) {
        int max_left = 0, max_right = 0;
        for (int j = i; j >= 0; j--) { //Search the left part for max bar size
            max_left = max(max_left, height[j]);
        }
        for (int j = i; j < size; j++) { //Search the right part for max bar size
            max_right = max(max_right, height[j]);
        }
        ans += min(max_left, max_right) - height[i];
    }
    return ans;
}

作者：LeetCode
链接：https://leetcode-cn.com/problems/trapping-rain-water/solution/jie-yu-shui-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

/*
* 在暴力方法中，我们仅仅为了找到最大值每次都要向左和向右扫描一次。但是我们可以提前存储这个值。因此，可以通过动态编程解决。
*/
class Solution_DP {
public:
    int trap(vector<int>& height) {
        //check
        int n = height.size();
        if(n <= 2) return 0;
        int sum = 0;
        std::vector<int> leftmax(n, 0);
        std::vector<int> rightmax(n, 0);
        leftmax[0] = height[0];
        rightmax[n-1] = height[n-1];
        for(int i = 1; i < n; i++) {
            leftmax[i] = std::max(leftmax[i-1], height[i]);
        }
        for(int i = n-2; i >= 0; i--) {
            rightmax[i] = std::max(rightmax[i+1], height[i]);
        }
        for(int i = 0; i < n; i++) {
            sum += std::min(rightmax[i], leftmax[i]) - height[i];
        }
        //return
        return sum;
    }
};

/*
我们可以认为如果一端有更高的条形块（例如右端），积水的高度依赖于当前方向的高度（从左到右）。
当我们发现另一侧（右侧）的条形块高度不是最高的，我们则开始从相反的方向遍历（从右到左）。
我们必须在遍历时维护 left_max 和 right_max ，但是我们现在可以使用两个指针交替进行，实现 1 次遍历即可完成。

作者：LeetCode
链接：https://leetcode-cn.com/problems/trapping-rain-water/solution/jie-yu-shui-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
class Solution_two_runner {
public:
    int trap(vector<int>& height) {
        //check
        int n = height.size();
        if(n <= 2) return 0;
        int sum = 0;
        int left = 0;
        int right = n-1;
        int leftmax = 0;
        int rightmax = 0;
        while(left < right) {
            if(height.at(right) > height.at(left)) {
                if(height.at(left) < leftmax) {
                    sum += leftmax - height.at(left);
                } else {
                    leftmax = height.at(left);
                }
                left++;
            } else {
                if(height.at(right) < rightmax) {
                    sum += rightmax - height.at(right);
                } else {
                    rightmax = height.at(right);
                }
                right--;
            }
        }
        //return
        return sum;
    }
};

int main() {
    Solution_DP sl;
    Solution_two_runner sr;
    std::vector<int> vt = {0,1,0,2,1,0,1,3,2,1,2,1};//false
    int num = sl.trap(vt);
    std::cout<<"trap rain water num : "<<num<<"\n";
    num = sr.trap(vt);
    std::cout<<"trap rain water num : "<<num<<"\n";
    return 0;
}