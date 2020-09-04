#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
3. Longest Substring Without Repeating Characters

Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <algorithm>
#include <queue>
#include <set>

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        std::unordered_set<char> st;
        int max = 0;
        int left = 0;
        for(int i = 0; i < s.size(); i++) {
            while(st.find(s.at(i)) != st.end()) {
                st.erase(s.at(left));
                left++;
            }
            st.insert(s.at(i));
            max = std::max(max, i - left + 1);
        }
        return max;
    }
};

int main() {
    Solution sl;
    std::string str = "pwwkew";
    int num = sl.lengthOfLongestSubstring(str);
    std::cout<<"lengthOfLongestSubstring : "<<num<<"\n";
    return 0;
}