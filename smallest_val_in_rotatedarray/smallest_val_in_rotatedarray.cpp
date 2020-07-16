#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>

/*
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。

Difficulty: 2~3 star
Finished by self: yes
*/

//Time complexity: average: O(log(n)), worst: O(log(n))
class Solution_by_binary_verbose {
public:
    int minNumberInRotateArray(std::vector<int> rotateArray) {
        int size = rotateArray.size();
        if(size <= 0 ) return 0;
        if(size == 1) return rotateArray.at(0);
        int left = 0;
        int right = size - 1;
        int mid = 0;
        while(left <= right) {
            //just deal with boundary cases, not try to unify them.
            if(left == right) return rotateArray.at(left);
            if(left + 1 == right) return rotateArray.at(left) < rotateArray.at(right) ?
                rotateArray.at(left) : rotateArray.at(right);
            mid = (left + right) / 2;
            if(rotateArray.at(mid) >= rotateArray.at(left) &&
              rotateArray.at(mid) >= rotateArray.at(right)) {
                left = mid;
            } else if (rotateArray.at(mid) <= rotateArray.at(left) &&
                   rotateArray.at(mid) <= rotateArray.at(right)) {
                right = mid;
            } else if (rotateArray.at(mid) <= rotateArray.at(left) &&
                   rotateArray.at(mid) <= rotateArray.at(right)) {
                return rotateArray.at(mid);
            }  
        } 
        return 0;
    }
};

/*
* Amazing simple solution!
* refer to https://www.nowcoder.com/questionTerminal/9f3231a991af4f55b95579b44b7a01ba?answerType=1&f=discussion
*/
//Time complexity: average: O(log(n)), worst: O(n)
class Solution_by_binary_search_simple {
public:
    int minNumberInRotateArray(std::vector<int> rotateArray) {
        int size = rotateArray.size();
        if(size <= 0 ) return 0;
        if(size == 1) return rotateArray.at(0);
        int left = 0;
        int right = size - 1;
        int mid = 0;
        while(left < right) {
            mid = (left + right) / 2;
            //absolute case
            if(rotateArray.at(left) < rotateArray.at(right)) return rotateArray.at(left);
            if(rotateArray.at(mid) > rotateArray.at(left)) {//absolute case
                left = mid + 1;
            } else if(rotateArray.at(mid) < rotateArray.at(right)) {//absolute case
                right = mid;
            } else {//for other cases, just narrow the range with ensuring min val
                left++;
            }
        } 
        return rotateArray.at(left);
    }
};

/*
* Crazily amazing simple solution!!!
链接：https://www.nowcoder.com/questionTerminal/9f3231a991af4f55b95579b44b7a01ba?answerType=1&f=discussion

这种二分查找难就难在，arr[mid]跟谁比.
我们的目的是：当进行一次比较时，一定能够确定答案在mid的某一侧。一次比较为 arr[mid]跟谁比的问题。

一般的比较原则有：
如果有目标值target，那么直接让arr[mid] 和 target 比较即可。
如果没有目标值，一般可以考虑**端点**
这里我们把target 看作是右端点，来进行分析，那就要分析以下三种情况，看是否可以达到上述的目标。

情况1，arr[mid] > target：4 5 6 1 2 3
arr[mid] 为 6， target为右端点 3， arr[mid] > target, 说明[first ... mid] 都是 >= target 的，
因为原始数组是非递减，所以可以确定答案为 [mid+1...last]区间,所以 first = mid + 1

情况2，arr[mid] < target:5 6 1 2 3 4
arr[mid] 为 1， target为右端点 4， arr[mid] < target, 说明答案肯定不在[mid+1...last]，
但是arr[mid] 有可能是答案,所以答案在[first, mid]区间，所以last = mid;

情况3，arr[mid] == target:
如果是 1 0 1 1 1， arr[mid] = target = 1, 显然答案在左边
如果是 1 1 1 0 1, arr[mid] = target = 1, 显然答案在右边
所以这种情况，不能确定答案在左边还是右边，那么就让last = last - 1;慢慢缩少区间，同时也不会错过答案。
*/
//Time complexity: average: O(log(n)), worst:  O(log(n))
class Solution_by_binary_search_with_fix_target {
public:
    int minNumberInRotateArray(std::vector<int> rotateArray) {
        int size = rotateArray.size();
        if(size <= 0 ) return 0;
        if(size == 1) return rotateArray.at(0);
        int left = 0;
        int right = size - 1;
        int mid = 0;
        while(left <= right) {
            //compare mid with target of right
            mid = (left + right) >> 1;
            if(rotateArray.at(mid) > rotateArray.at(right)) {
                left = mid + 1;
            } else if (rotateArray.at(mid) < rotateArray.at(right)) {
                right = mid;
            } else {
                right--;
            }
        }
        return rotateArray.at(left);
    }
};

void traversevector(std::vector<int> &vt)
{
    unsigned int i = 0;
    std::cout<<"vector list: [";
    for(i = 0; i < vt.size(); i++) {
        std::cout<<vt.at(i)<<" ";
    }
    std::cout<<"]\n";
}

int main()
{
    std::vector<int> vt1 = {4, 5, 6, 1, 2, 3};
    std::vector<int> vt2 = {5, 6, 1, 2, 3, 4};
    std::vector<int> vt3 = {1, 0, 1, 1, 1};
    std::vector<int> vt4 = {1, 1, 1, 0, 1};
    std::vector<int> vt5 = {2, 1};
    std::vector<int> vt6 = {1, 2};
    std::vector<int> vt7 = {1};
    std::vector<std::vector<int>> vt = {vt1, vt2, vt3, vt4, vt5, vt6, vt7};
    Solution_by_binary_search_with_fix_target *sl = new Solution_by_binary_search_with_fix_target();
    int min = -1;
    unsigned int i = 0;
    for(i = 0; i < vt.size(); i++) {
        min = sl->minNumberInRotateArray(vt.at(i));
        traversevector(vt.at(i));
        std::cout<<"min in rorated array is "<<min<<"\n\n";
    }
    delete sl;
    
    Solution_by_binary_search_simple *ss = new Solution_by_binary_search_simple();
    min = -1;
    i = 0;
    for(i = 0; i < vt.size(); i++) {
        min = ss->minNumberInRotateArray(vt.at(i));
        traversevector(vt.at(i));
        std::cout<<"min in rorated array is "<<min<<"\n\n";
    }
    delete ss;

    Solution_by_binary_verbose *sv = new Solution_by_binary_verbose();
    min = -1;
    i = 0;
    for(i = 0; i < vt.size(); i++) {
        min = sv->minNumberInRotateArray(vt.at(i));
        traversevector(vt.at(i));
        std::cout<<"min in rorated array is "<<min<<"\n\n";
    }
    delete sv;

    (void) min;

    return 0;
}
