#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <vector>
using namespace std;

/*
JZ30 最大连续子序列的和

HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。
今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。
但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。
给一个数组，返回它的最大连续子序列的和，你会不会被他忽悠住？(子向量的长度至少是1)
*/
class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        //check
        if(array.size() == 1 ) return array[0];
        //dp, for i = 0 to i = size-1
        //if x(i) < 0, caculate max, otherwise, dp(i)=dp(i-1)+x(i)
        //finally, sort vector x(i), return vt[size-1]
        int max = array[0];
        std::vector<int> dp(array.size(), 0);
        dp[0] = array[0];
        for(int i = 1; i < array.size(); i++) {
            dp[i] = std::max(array[i], dp[i-1]+array[i]);
            max = std::max(max, dp[i]);
        }
        //return max
        return max;
    }
};

//遍历法，连续和大于0则继续尝试添加元素到集合，否则重置集合，若数组均负数，则取其中最大值
/*
class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        int ret = array[0];
        int tmp = 0;
        for (const int k : array) {
            if (tmp + k < 0) {
                tmp = 0;
            }
            else {
                tmp += k;
            }
            ret = max(ret, tmp);
        }
        if (tmp != 0)
            return ret;
        return *max_element(array.begin(), array.end());
    }
};
*/
int main()
{
    std::vector<int> vt = {6,-3,-2,7,-15,1,2,2};
    Solution sl;
    int res = sl.FindGreatestSumOfSubArray(vt);
    std::cout<<"FindGreatestSumOfSubArray in {6,-3,-2,7,-15,1,2,2}, max sum :"<<res<<"\n";
    return 0;
}
