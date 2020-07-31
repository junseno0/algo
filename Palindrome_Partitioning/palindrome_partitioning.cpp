#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

class Solution_v1 {
public:
    vector<vector<string>> ret;
    bool isRingString(string str) {
        int l = 0;
        int r = str.size()-1;
        while(l <= r) {
            if(str[l] != str[r]) return false;
            l++;
            r--;
        }
        return true;
    }
    void findRing(string& s, int pos, vector<string> path) {
        if(pos > s.size()) return;
        if(pos == s.size()) {
            ret.push_back(path);
            path.clear();
            return;
        }

        for(int i = 1; i <= s.size()-pos; i++) {
            if(isRingString(s.substr(pos, i)))
                path.push_back(s.substr(pos,i));
            else
                continue;
            findRing(s, pos+i, path);
            path.pop_back();//trick, backtrack!!
        }
    }
    vector<vector<string>> partition(string s) {
        vector<string> path;
        findRing(s, 0, path);
        return ret;
    }
};

/*
* 添加“备忘录”，但是时间内存依然性能不足。
*/
class Solution_v2_add_memo {
public:
    vector<vector<string>> ret;
    bool isRingString(string &s, int startpos, int len, vector<vector<int>> &memo) {
        if(memo[startpos][len] == 1) return true;
        if(memo[startpos][len] == 0) return false;
        int l = startpos;
        int r = startpos+len-1;
        while(l <= r) {
            if(s[l] != s[r]) {
                memo[startpos][len] = 0;
                return false;
            }
            l++;
            r--;
        }
        memo[startpos][len] = 1;
        return true;
    }
    void findRing(string& s, int pos, vector<string> path, vector<vector<int>> &memo) {
        if(pos > s.size()) return;
        if(pos == s.size()) {
            ret.push_back(path);
            path.clear();
            return;
        }

        for(int i = 1; i <= s.size()-pos; i++) {
            std::string substr = s.substr(pos, i);
            if(isRingString(s, pos, i, memo))
                path.emplace_back(substr);
            else
                continue;
            findRing(s, pos+i, path, memo);
            path.pop_back();//trick
        }
    }
    vector<vector<string>> partition(string s) {
        vector<string> path;
        vector<vector<int>> memo(s.size(), vector<int>(s.size()+1, -1));//trick here. size+1
        findRing(s, 0, path, memo);
        return ret;
    }
};

int main() {

    //Solution sl;
    Solution_v1 sl;
    std::string s = "aab";
    std::vector<std::vector<std::string>> vs = sl.partition(s);
    for(auto itt: vs) {
        for(auto it: itt) {
            std::cout<<"["<<it<<"]";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
    return 0;
}