#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <string>
/*
Count the number of times a number appears in the sorted array.

Difficulty: 1 star
Finished by self: yes
*/

//Time complexity: average: O(nlogn)
//Space complexity: average: O(1)
class Solution_by_recursive_binary_search {
public:
    int GetNumberOfK(std::vector<int> data ,int k, int left, int right) {
        if(left > right) return 0;
        //check min and max
        if(data.at(left) > k || data.at(right) < k) return 0;
        if(data.at(left) == k && data.at(right) == k) return right - left + 1;
        return GetNumberOfK(data, k, left, (left+right)/2) +
            GetNumberOfK(data, k , (left+right)/2 + 1, right);
    }
    int GetNumberOfK(std::vector<int> data ,int k) {
        //check
        if(data.size() <= 0) return 0;
        //check min and max
        if(data.front() > k || data.back() < k) return 0;
        return GetNumberOfK(data, k, 0, data.size() - 1);
    }
};

class Solution_by_binary_search_v1 {
public:
    int GetNumberOfK(std::vector<int> data ,int k) {
        //check
        if(data.size() <= 0) return 0;
        //check min and max
        if(data.front() > k || data.back() < k) return 0;
        //find right with binary serach
        //boundary case: val(right+1) > k, right+1 <= size-1
        int count = 0;
        int left = 0;
        int right = data.size() - 1;
        data.push_back(data.back()+1);
        while(left < right) {
            if(data.at(right) == k && data.at(right+1) > k) break;
            if(data.at((left + right)/ 2) == k) {
                right--;
            } else if(data.at((left + right)/2) > k) {
                right = (left + right) / 2 - 1;
            } else {
                left = (left + right) / 2 + 1;
            }
        }
        if(left == right && data.at(left) != k) return 0;
        //find left with binary search
        //boundary case: val(left-1) < k 
        left = 0;
        while(left < right){
            if(data.at(left) == k ) break;
            if(data.at((left + right)/ 2) == k) {
                left++;
            } else if(data.at((left + right)/2) > k) {
                right = (left + right)/2 - 1;
            } else {
                left = (left + right)/2 + 1;
            }
        }
        count = right - left + 1;
        return count;
    }
};

class Solution_by_binary_search_v2 {
public:
    int GetNumberOfK(std::vector<int> data ,int k) {
        //check first
        int lbound = 0, rbound = 0;
        // find left bound
        int left = 0;
        int right = data.size();// NOT size - 1, otherwise, loop is avoided.
        int mid = 0;
        //Loop case: left < right
        while(left < right) {
            mid = (left + right) / 2;
            //just draw and think mid as left or right
            //then comes out that left and right should be as what
            if(data.at(mid) < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        lbound = left;
        // find right bound
        //Loop case: : left < right
        left = 0;
        right = data.size();// NOT size - 1, data.at(size) NOT be visited.
        while(left < right) {
            mid = (left + right) / 2;
            if(data.at(mid) > k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        rbound = right;
        return rbound - lbound;
    }
};

class Solution_by_binary_search_stl {
public:
    int GetNumberOfK(std::vector<int> nums ,int target) {
        return std::upper_bound(nums.begin(), nums.end(), target)
            - std::lower_bound(nums.begin(), nums.end(), target);
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
    std::vector<int> vt1 = {1, 3, 321};
    std::vector<int> vt2 = {1, 3, 3, 4, 5, 6};
    std::vector<int> vt3 = {1, 1, 2, 2, 2};
    std::vector<std::vector<int>> vt = {vt1, vt2, vt3};
    unsigned int i = 0;
    int count = 0;
    int target = 2;

    Solution_by_recursive_binary_search sr;
    for(i = 0; i < vt.size(); i++) {
        count = sr.GetNumberOfK(vt.at(i), target);
        traversevector(vt.at(i));
        std::cout<<"Solution_by_recursive_binary_search. GetNumberOfK : "<<count<<"\n";
        std::cout<<"\n";
    }

    Solution_by_binary_search_v1 st;
    for(i = 0; i < vt.size(); i++) {
        count = st.GetNumberOfK(vt.at(i), target);
        traversevector(vt.at(i));
        std::cout<<"Solution_by_iterative_binary_search. GetNumberOfK : "<<count<<"\n";
        std::cout<<"\n";
    }

    Solution_by_binary_search_stl ss;
    for(i = 0; i < vt.size(); i++) {
        count = ss.GetNumberOfK(vt.at(i), target);
        traversevector(vt.at(i));
        std::cout<<"Solution_by_binary_search_stl. GetNumberOfK : "<<count<<"\n";
        std::cout<<"\n";
    }
    return 0;
}
