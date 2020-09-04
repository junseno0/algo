#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>
#include <unordered_map>
using namespace std;

/*
438. Find All Anagrams in a String

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-all-anagrams-in-a-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


//labuladong的思维框架非常有用，结合例子想象成一个公司的新员工入职老员工离职，但公司时刻保持窗口人数，总有一些时刻，目标岗位及其人数都满足老总要求
//https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/solution/hua-dong-chuang-kou-tong-yong-si-xiang-jie-jue-zi-/
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        //check

        //slidind window
        int left = 0;
        int right = 0;
        std::vector<int> vt;
        //shrink case: one word found; a non-expected char catch
        std::unordered_map<char, int> need, window;
        for(char c : p) {
            need[c]++;
        }
        int valid = 0;
        while(right < s.size()) {
            //extend window
            char c = s.at(right);
            right++;
            if(need.count(c) != 0) {
                window[c]++;
                if(need[c] == window[c])
                    valid++;
            }
            //shrink window
            while(right - left >= p.size()) {//p.size indicates how many jobs
                if(valid == need.size())//trick, valid indicates how many kinds of jobs
                    vt.push_back(left);
                c = s.at(left);
                left++;

                if(need.count(c) != 0) {//trick, if NOT in target jobs, dont't care.
                    if(need[c] == window[c]) {
                        valid--;
                    }
                    window[c]--;
                }
            }
        }

        //return vt
        return vt;
    }
};

int main() {
    std::string str = "cbaebabacd";
    Solution sl;
    std::vector<int> res = sl.findAnagrams(str, string("abc"));
    for(auto it : res)
        std::cout<<"sl find anagrams count: "<<it<<" \n";
    return 0;
}