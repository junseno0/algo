#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <queue>
/*
汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。
对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，
即“XYZdefabc”。是不是很简单？OK，搞定它！

There is a shift instruction in assembly language called Rotate Left (ROL).
Now there is a simple task, which is to simulate the operation result of this instruction with a string.
For a given character sequence S, please output the sequence after circularly shifting it K bits to the left.
For example, the character sequence S="abcXYZdef", it is required to output the result of the circular
shift left by 3 bits, that is, "XYZdefabc". Is not it simple? OK, get it done!

Difficulty: 1 star
Finished by self: yes
*/

class Solution_by_substr {
public:
    std::string LeftRotateString(std::string str, int n) {
        if(str.length() <= 1 || n == 0) return str;
        n =  n % str.length();
        std::string st1 = str.substr(0, n);
        std::string st2 = str.substr(n);
        return st2+st1;
    }
};
/*
Optimized code.

class Solution {
public:
    string LeftRotateString(string str, int n) {
        if (n > str.size()) return str;
        return str.substr(n) + str.substr(0, n);
    }
};

class Solution {
public:
    string LeftRotateString(string str, int n) {
        return (n > str.size()) ? str : (str + str).substr(n, str.size());
    }
};
*/

/*
* NOT use STL function substr. Implement it.
* "/" and "%" is easy to be invalid.
*/
class Solution_by_own_substr {
public:
    std::string mysubstr(std::string str, int pos, int n) {
        //check
        std::string ret = "";
        if(str.size() < pos + n || str.size() <= 0) return ret;
            //get char by at, append char to new string
        for(int i = pos; i < pos + n; i++) {
            ret += str.at(i);
        }
        return ret;
    }
    std::string LeftRotateString(std::string str, int n) {
        if(str.length() <= 1 || n == 0) return str;
        n =  n % str.length();
        return mysubstr(str, n, str.size() - n) + mysubstr(str, 0, n);
    }
};

class Solution_by_reverse {
public:
    std::string reversestr(std::string str, int pos, int n) {
        //check
        std::string ret = "";
        if(str.size() < pos + n || str.size() <= 0) return ret;
            //get char by at, append char to new string
        for(int i = pos + n - 1; i >= pos; i--) {
            ret += str.at(i);
        }
        return ret;
    }
    std::string LeftRotateString(std::string str, int n) {
        //check
        if(str.length() <= 1 || n == 0) return str;
        n =  n % str.length();
        std::string str_re = reversestr(str, 0, n) + reversestr(str, n, str.size() - n);
        return reversestr(str_re, 0, str.size());
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
    std::string s1 = "freeman";
    std::string s2 = "f";
    std::string s3 = "";
    std::vector<std::string> vt = {s1, s2, s3};
    Solution_by_substr ss;
    for(auto it : vt) {
        std::string str = ss.LeftRotateString(it, 4);
        std::cout<<"Solution_by_substr. LeftRotateString : "<<str<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n";

    Solution_by_own_substr so;
    for(auto it : vt) {
        std::string str = so.LeftRotateString(it, 4);
        std::cout<<"Solution_by_own_substr. LeftRotateString : "<<str<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n";
 
    Solution_by_reverse sr;
    for(auto it : vt) {
        std::string str = sr.LeftRotateString(it, 4);
        std::cout<<"Solution_by_reverse. LeftRotateString : "<<str<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n";
    return 0;
}
