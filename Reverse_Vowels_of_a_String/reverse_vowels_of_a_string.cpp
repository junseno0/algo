#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>
#include <unordered_set>
using namespace std;

class Solution_v1 {
public:
    string reverseVowels(string s) {
        std::unordered_set<char> record;
        std::vector<char> res ={'a','e','i','o','u','A','E','I','O','U'};
        for(auto it : res) {
            record.insert(it);
        }
        int left = 0;
        int right = s.size() - 1;
        while(left < right) {
            while(left < right && record.find(s[left]) == record.end()) {
                left++;
            }
            while(left < right && record.find(s[right]) == record.end()) {
                right--;
            }
            if(left < right) {
                std::swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        return s;
    }
};

class Solution_v2 {
private:
int vowel(char c)
{
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        return 1;
    else
        return 0;
}

public:
    string reverseVowels(string s) {
        int left = 0;
        int right = s.size() - 1;
        while(left < right) {
            while(left < right && !vowel(s[left])) {
                left++;
            }
            while(left < right && !vowel(s[right])) {
                right--;
            }
            if(left < right) {
                std::swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        return s;
    }
};

int main() {
    Solution_v2 sl;
    std::string res = sl.reverseVowels(string("hello"));
    std::cout<<"sl hello reverseVowels : "<<res<<" \n";
    res = sl.reverseVowels(string("oboboa"));
    std::cout<<"sl oboboa reverseVowels : "<<res<<" \n";
    return 0;
}