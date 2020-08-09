#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>
#include <unordered_map>
using namespace std;

/*
 Remove Duplicates from Sorted Array II
*/

class Solution_v1 {
public:
    int removeDuplicates(vector<int>& nums) {
        //check

        //double pointer
        int left = 0;
        int right = 0;
        std::unordered_map<int, int> record;
        for(right = 0; right < nums.size(); right++ ) {
            //move right
            //if no in map, erase map and insert it
            //if once in map, insert it
            //if two in map, keep move
            while(right < nums.size()) {
                if(record.find(nums[right]) == record.end()) {
                    record.clear();
                    record.insert(make_pair(nums[right], 1));
                    break;
                } else if (record[nums[right]] == 1) {
                    record[nums[right]]++;
                    break;
                } else if (record[nums[right]] == 2) {
                    right++;
                }
            }

            //swap left and right
            if(right < nums.size()) {
                nums[left] = nums[right];
                left++;
            }
        }

        //return
        return left;
    }
};

class Solution_v2_2_runner {
public:
    int removeDuplicates(vector<int>& nums) {
        //check
        if(nums.size() < 3) return nums.size();
        //double pointer
        int index = 2;
        for(int i = 2; i < nums.size(); i++) {
            //if not duplicated, assign cur one to index one
            if(nums[index-2] != nums[i]) {
                nums[index] = nums[i];
                index++;
            }
        }
        return index;
    }
};

/*
https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array-ii/solution/shuang-zhi-zhen-zhi-tong-xiang-zhi-zhen-che-di-jie/
*/
class Solution_v3_2_runner {
public:
    int removeDuplicates(vector<int>& nums) {
        //check
        if(nums.size() < 3) return nums.size();
        //double pointer
        int index = 1;
        for(int i = 2; i < nums.size(); i++) {
            //if not duplicated, assign cur one to index one
            if(nums[index-1] != nums[i]) {
                index++;
                nums[index] = nums[i];
            }
        }
        return index+1;
    }
};

int main() {
    Solution_v3_2_runner sl;
    std::vector<int> vt = {1, 1, 2, 2, 2, 3, 5};
    int count = sl.removeDuplicates(vt);
    std::cout<<"sl remove duplicates: \n";
    for(int i = 0; i < count; i++)
        std::cout<<"["<<vt.at(i)<<"] ";
    return 0;
}