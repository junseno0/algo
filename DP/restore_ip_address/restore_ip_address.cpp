#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

class Solution_v1 {
public:
    std::vector<string> ret;

    void findIp(string &s, int stringcount, int index, string& prestr) {
        if((s.size()-index) > stringcount * 3 || index > s.size()) return;
        if(stringcount == 0 && index == s.size() ) {
            //save prestr to ret
            prestr.erase(prestr.end()-1);//erase last '.'
            ret.push_back(prestr);
            return;
        }
        if(stringcount == 0) return;
        //add "."
        //substr not start with '0'
        std::string newprestr = prestr+s.substr(index, 1)+".";
        if(index < s.size())
            findIp(s, stringcount-1, index+1, newprestr);
 
        newprestr = prestr+s.substr(index, 2)+".";
        if(index+1 < s.size() && atoi(s.substr(index, 2).c_str()) > 9)
            findIp(s, stringcount-1, index+2, newprestr);
 
        newprestr = prestr+s.substr(index, 3)+".";
        if(index+2 < s.size() && atoi(s.substr(index, 3).c_str()) > 99 && atoi(s.substr(index, 3).c_str()) <= 255)
            findIp(s, stringcount-1, index+3, newprestr);
 
        return;
    }

    vector<string> restoreIpAddresses(string s) {
        ret.clear();
        if(s.size() == 0) return ret;
        string prestr = "";
        findIp(s, 4, 0, prestr);
        return ret;
    }
};

class Solution_v2 {
public:
    std::vector<string> ret;
    bool valid(string str) {
        if(str.size() == 1) return true;
        if(str.size() == 2 && stoi(str) > 9) return true;
        if(str.size() == 3 && stoi(str) > 99 && stoi(str) <= 255) return true;
        return false;
    }
    void findIp(string &s, int stringcount, int index, string& prestr) {
        if((s.size()-index) > stringcount * 3 || index > s.size()) return;
        if(stringcount == 0 && index == s.size() ) {
            //save prestr to ret
            prestr.erase(prestr.end()-1);//erase last '.'
            ret.push_back(prestr);
            return;
        }
        if(stringcount == 0) return;
        for(int i = 0; i < 3; i++) {
            if(!valid(s.substr(index,i+1))) continue;
            string newprestr = prestr+s.substr(index, i+1) + ".";
            findIp(s, stringcount-1, index+i+1, newprestr);
        }    
 
        return;
    }

    vector<string> restoreIpAddresses(string s) {
        ret.clear();
        if(s.size() == 0) return ret;
        string prestr = "";
        findIp(s, 4, 0, prestr);
        return ret;
    }
};

/*最优美的暴力解法*/
/*
    public List<String> restoreIpAddresses(String s) {
        List<String> ret = new ArrayList<>();

        StringBuilder ip = new StringBuilder();
        
        for(int a = 1 ; a < 4 ; ++ a)
            for(int b = 1 ; b < 4 ; ++ b)
                for(int c = 1 ; c < 4 ; ++ c)
                    for(int d = 1 ; d < 4 ; ++ d)
                    {
                        if(a + b + c + d == s.length() )
                        {
                            int n1 = Integer.parseInt(s.substring(0, a));
                            int n2 = Integer.parseInt(s.substring(a, a+b));
                            int n3 = Integer.parseInt(s.substring(a+b, a+b+c));
                            int n4 = Integer.parseInt(s.substring(a+b+c));
                            if(n1 <= 255 && n2 <= 255 && n3 <= 255 && n4 <= 255)
                            {
                                ip.append(n1).append('.').append(n2)
                                        .append('.').append(n3).append('.').append(n4);
                                if(ip.length() == s.length() + 3) ret.add(ip.toString());
                                ip.delete(0, ip.length());
                            }
                        }
                    }
        return ret;
    }

作者：reals
链接：https://leetcode-cn.com/problems/restore-ip-addresses/solution/ke-neng-shi-zui-you-mei-de-bao-li-jie-fa-liao-by-u/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

/*相对标准的回溯套路，回溯算法的典型模式，循环递归，TODO*/
/*
class Solution {
public:
    bool isValid(string ip)
{
    int val = stoi(ip);
    if (val > 255)    return false;
    if (ip.size() >= 2 && ip[0] == '0')    return false;
    return true;
}
void dfs(string& s, int pos, vector<string> &path, vector<string>& res)
{
    //首先判断剩余的位数，是不是还能满足要求，比如25525511135，若2.5.5.25511135显然不满足，这可以预判
    //4组，每组最多3位数字
    int maxLen = (4 - path.size()) * 3;
    if (s.size() - pos > maxLen)    return;
    if (path.size() == 4 && pos == s.size()) {
        string ans = "";
        for (int i = 0; i < 4; ++i) {
            ans += path[i];
            if (i != 3)    ans += ".";
        }
        res.push_back(ans);
        return;
    }
    //回溯算法的典型模式，循环递归
    for (int i = pos; i < s.size() && i <= pos + 2; ++i) {
        string ip = s.substr(pos, i - pos+1);
        if (!isValid(ip))    continue;
        path.push_back(ip);
        dfs(s, i + 1, path, res);
        path.pop_back();
    }
}
vector<string> restoreIpAddresses(string s) 
{
    //找3个.的位置,每个.之前组成的的数值必须要小于255，且以0开头的除非数字是0本身，否则也是非法
    vector<string> res;
    if (s.size() == 0 || s.size() < 4)    return res;
    vector<string> path;//存储从根开始的到叶子节点的满足条件的路径,因为最多3位数字一组，所以同一层横向循环时尝试最多3个位的长度
    dfs(s, 0, path, res);
    return res;
}
};

作者：ali40
链接：https://leetcode-cn.com/problems/restore-ip-addresses/solution/cqing-xi-yi-dong-jie-fa-by-ali40/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

/*非常简洁的C++解法，不传递原字符串，不符合条件的跳过剪枝，实时IP传递，满足字符串个数为4且剩余字符数为0的IP满足条件*/
/*
class Solution {
public:
	vector<string> restoreIpAddresses(string s) {
		string ip;
		helper(s, 0, ip);
		return res;
	}
	void helper(string s, int n, string ip) {
		if (n == 4) {
			if (s.empty()) res.push_back(ip); 
		}
		else {
			for (int k = 1; k < 4; ++k) {
				if (s.size() < k) break;
				int val = stoi(s.substr(0, k));
				//值大于255或者以0开头不符合IP规定,可以剪枝
				if (val > 255 || k != std::to_string(val).size()) continue; 
				helper(s.substr(k), n + 1, ip + s.substr(0, k) + (n == 3 ? "" : "."));
			}
		}
		return;
	}
private:
	vector<string> res;
};

作者：codave
链接：https://leetcode-cn.com/problems/restore-ip-addresses/solution/cdi-gui-hui-su-jian-zhi-by-codave/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

int main() {

    //Solution sl;
    Solution_v2 sl;
    std::string s = "25525511133";
    std::vector<string> vs = sl.restoreIpAddresses(s);
    for(auto it : vs) std::cout<<"["<<it<<"] ";
    std::cout<<"\n";

    return 0;
}