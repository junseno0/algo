#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>
#include <unordered_map>
using namespace std;

/*
567. Permutation in String

Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.

 

Example 1:

Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/permutation-in-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        //check

        //sliding window
        int left = 0;
        int right = 0;
        std::unordered_map<char, int> need;
        std::unordered_map<char, int> window;
        int valid = 0; //how many jobs
        for(char c : s1) {
            need[c]++;
        }
        while(right < s2.size()) {
            //extend window
            char c = s2.at(right);
            right++;
            if(need.count(c) > 0) {
                window[c]++;
                if(need[c] == window[c])
                    valid++;
            }

            //try to shrink window, if expected ok, store res
            while(right - left >= s1.size()) {
                //check valid count expected
                if(valid == need.size()) return true;
                //shrink by move left ahead
                //if removed one is in need jobs, decrease num in window, maybe validcount
                c = s2.at(left);
                left++;
                if(need.count(c) > 0) {
                    if(need[c] == window[c])
                        valid--;
                    window[c]--;
                }
            }
        }

        //return
        return false;
    }
};

int main() {
    Solution sl;
    bool flag = sl.checkInclusion(string("ab"), string("eidbaooo"));
    std::cout<<"sl eidbaooo checkInclusion : "<<flag<<" \n";
    flag = sl.checkInclusion(string("ab"), string("oboboa"));
    std::cout<<"sl oboboa checkInclusion : "<<flag<<" \n";
    return 0;
}