#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>
/*
There is a number in the array that appears more than half the length of the array.
Please find this number. For example, enter an array of length {1,2,3,2,2,2,5,4,2}. 
Since the number 2 appears in the array 5 times, more than half the length of the array, 
so output 2. If it does not exist, output 0.

Difficulty: 2~3 star
Finished by self: yes
*/

//Time complexity: average: O(nlogn)
//Space complexity: average: O(1)
//STL sort is available
class Solution_by_sort {
public:
    // pass parameter by reference or pointer
    void QuickSort2(std::vector<int>& numbers, int left, int right) {
        //check
        //set anchor, smaller left, bigger right
        if(left >= right) return;
        int ll = left;
        int r = right;
        //recurse each half for the same way
        //until left >= right
        int anchor = numbers.at(left);
        while(left < right) {
            while(left < right) {
                if(numbers.at(right) <= anchor) {
                    //while find val(right) smaller then anchoer
                    //put val(right) to left, empty right, switch to left to find bigger one
                    numbers.at(left) = numbers.at(right);
                    left++;
                    break;
                }
                right--;
            }
            while(left < right) {
                if(numbers.at(left) > anchor) {
                    //put val(left) to right, empty left, switch to right to find smaller one
                    numbers.at(right) = numbers.at(left);
                    right--;
                    break;
                }
                left++;
            }
        }
        numbers.at(left) = anchor;
        QuickSort2(numbers, ll, left-1);
        QuickSort2(numbers, left+1, r);
    }
    void QuickSort(std::vector<int>& numbers) {
        if(numbers.size() == 0 || numbers.size() == 1) return;
        QuickSort2(numbers, 0, numbers.size()-1);
    }
    int MoreThanHalfNum_Solution(std::vector<int> numbers) {
        //check
        if(numbers.size() == 0 ) return 0;
        if(numbers.size() == 1 ) return numbers.at(0);
        //sort
        QuickSort(numbers);
        //check appearing times for each val in array, skip same vals
        //if > size/2, pick it out.
        int pre = 0;
        int cur = 0;
        while(cur < numbers.size()) {
            while(cur < numbers.size() && numbers.at(pre) == numbers.at(cur)) {
                cur++;
            }
            if ((cur - pre) > numbers.size()/2) return numbers.at(pre);
            pre = cur;
        }
        //return val
        return 0;
    }
};

/*
* Refer to：https://www.nowcoder.com/questionTerminal/e8a1b01a2df14cb2b228b30ee6a92163?answerType=1&f=discussion
* 如果有符合条件的数字，则它出现的次数比其他所有数字出现的次数和还要多。
* 在遍历数组时保存两个值：一是数组中一个数字，一是次数。遍历下一个数字时，若它与之前保存的数字相同，
* 则次数加1，否则次数减1；若次数为0，则保存下一个数字，并将次数置为1。遍历结束后，所保存的数字即为所求。
* 然后再判断它是否符合条件即可。
* 这实际上就是“分形叶”法，对数组同时去掉两个不同的数字，到最后剩下的一个数就是该数字。
* 如果剩下两个，那么这两个也是一样的，就是结果，在其基础上把最后剩下的一个数字或者两个回到原来数组中，
* 将数组遍历一遍统计一下数字出现次数进行最终判断。
*/
//Time complexity: average: O(n)
//Space complexity: average: O(1)
class Solution_by_candidate {
public:
    int MoreThanHalfNum_Solution(std::vector<int> numbers) {
        //check
        if(numbers.size() == 0 ) return 0;
        if(numbers.size() == 1 ) return numbers.at(0);
        //by candidate method
        int candidate = 0;
        unsigned int cnt = 0;
        int val = 0;
        for(unsigned int i = 0; i < numbers.size(); i++) {
            val = numbers.at(i);
            if(cnt == 0){
                candidate = val;
                cnt++;
                continue;
            }
            if (candidate == val) {
                cnt++;
            } else {
                cnt--;
            }
        }
        if(cnt == 0) return 0;
        //check val again
        cnt = 0;
        for(unsigned int i = 0; i < numbers.size(); i++) {
            if(numbers.at(i) == candidate) cnt++;
        }
        if(cnt > numbers.size() / 2) return candidate;
        return 0;
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
    std::vector<int> vt1 = {4, 5, 4, 4, 4, 3};
    std::vector<int> vt2 = {5, 6, 1, 1, 3, 3};
    std::vector<int> vt3 = {1, 1};
    std::vector<int> vt4 = {1};
    std::vector<int> vt5 = {};
    std::vector<std::vector<int>> vt = {vt1, vt2, vt3, vt4, vt5};
    unsigned int i = 0;
    int val = 0;
    Solution_by_candidate sc;
    for(i = 0; i < vt.size(); i++) {
        val = sc.MoreThanHalfNum_Solution(vt.at(i));
        traversevector(vt.at(i));
        std::cout<<"MoreThanHalfNum_Solution. val : "<<val<<"\n";
        std::cout<<"\n";
    }

    Solution_by_sort st;
    for(i = 0; i < vt.size(); i++) {
        val = st.MoreThanHalfNum_Solution(vt.at(i));
        traversevector(vt.at(i));
        std::cout<<"MoreThanHalfNum_Solution. val : "<<val<<"\n";
        std::cout<<"\n";
    }

    return 0;
}
