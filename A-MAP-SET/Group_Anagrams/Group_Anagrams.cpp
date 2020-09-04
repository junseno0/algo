#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>
#include <map>
using namespace std;

/*
49. Group Anagrams
Given an array of strings, group anagrams together.

Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/group-anagrams
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。。
*/

/*
因为要找组成一样的单词，如何判断？
最简单的，一排序，如果是同一个单词，那么就是组成一样的
比如 “eat” "tea" 排序后都为 “aet”
只要引入一个hash表，索引是排序后的单词，值为结果vector的下标，循环一遍就好了

作者：rjs
链接：https://leetcode-cn.com/problems/group-anagrams/solution/c-yin-ru-hashbiao-shi-jian-32ms-ji-bai-9948-nei-cu/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        //check
        std::vector<std::vector<std::string>> res;
        res.clear();
        std::string tmp;
        std::map<string, int> record;
        //map, sort, count, add, push_back
        for(auto str : strs) {
            tmp = str;
            std::sort(tmp.begin(), tmp.end());
            if(record.count(tmp)) {
                res[record[tmp]].push_back(str);
            } else {
                //if no in map, new one, put it in map and res and then contunue
                record[tmp] = res.size();//if first string, record["eat"] = 0
                std::vector<string> vt;
                vt.push_back(str);
                res.push_back(vt);
            }
        }

        //return
        return res;
    }
};

int main() {
    Solution sl;
    std::vector<string> vt= {"eat", "tea", "tan", "ate", "nat", "bat"};
    std::vector<std::vector<string>> res = sl.groupAnagrams(vt);
    for(auto itt : res) {
        for(auto it : itt)
            std::cout<<"["<<it<<"] ";
        std::cout<<"\n";
    }
    return 0;
}