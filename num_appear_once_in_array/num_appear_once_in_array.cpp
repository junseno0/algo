#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>
/*
Except for two numbers in an integer array, all other numbers appear twice. Please write a program to find these two numbers that only appear once.

Difficulty: 1 star
Finished by self: yes
*/

//Time complexity: average: O(n)
//Space complexity: average: O(n)
//Attention: "()" is necessary and importent for  &/^/| operations.
class Solution_by_bit_operation {
public:
    void FindNumsAppearOnce(std::vector<int> data,int* num1,int *num2) {
        //check
        if(data.size() == 0) return;
        // xor all data as result
        int result = 0;
        int i = 0;
        for(i = 0; i < data.size(); i++) {
            result ^= data.at(i);
        }
        //result is xor by num1 and num2
        //result as 0x1001, i.e, 0x0001, it means num1 xor num2, num1 as 1 and num2 as 0
        //find onx pos with 1
        int index = 1;
        while((index & result) == 0) {
            index = index << 1;
        }
        //0x0001, "and" with all data, if yes, xor it. result comes from num1, why, since pairs result into 0
        //if no, xor it, result comes from num2, why, since pairs result into 0, num2 alone
        for(i = 0; i < data.size(); i++) {
            if((index & data.at(i)) == 0) {
                *num1 ^= data.at(i);
            } else {
                *num2 ^= data.at(i);
            }
        }
        return;
    }
};

class Solution_by_set {
public:
    void FindNumsAppearOnce(std::vector<int> data,int* num1,int *num2) {
        //check
        if(data.size() == 0) return;
        std::set<int> st;
        for(int i = 0; i < data.size(); i++) {
            if(st.count(data.at(i))) {
                st.erase(data.at(i));
            } else {
                st.insert(data.at(i));
            }
        }
        *num1 = *st.begin();
        st.erase(*num1);
        *num2 = *st.begin();
        return;
    }
};

class Solution_by_map {
public:
    void FindNumsAppearOnce(std::vector<int> data,int* num1,int *num2) {
        //check
        if(data.size() == 0) return;
        std::map<int, int> mp;
        std::vector<int> vt;
        for(int i = 0; i < data.size(); i++) {
            ++mp[data.at(i)];
        }
        for(int i = 0; i < data.size(); i++) {
            if(mp[data.at(i)] == 1) {
                vt.push_back(data.at(i));
            }
        }
        *num1 = vt.at(0);
        *num2 = vt.at(1);
        return;
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

/*
* Bug-free 代码，首先检查编译问题，包括头文件是否齐全，标准空间是否声明，函数调用符是否正确
* 变量名是否一一对应，引用与指针传递是否正确，返回是否正确类型
*/
int main()
{
    std::vector<int> vt1 = {4, 5, 4, 5, 2, 3};
    std::vector<int> vt2 = {5, 6, 1, 1, 3, 3};
    std::vector<int> vt3 = {0, 1};
    std::vector<std::vector<int>> vt = {vt1, vt2, vt3};
    int i = 0;
    int num1 = 0;
    int num2 = 0;
    Solution_by_bit_operation sb;
    for(i = 0; i < vt.size(); i++) {
        sb.FindNumsAppearOnce(vt.at(i), &num1, &num2);
        traversevector(vt.at(i));
        std::cout<<"FindNumsAppearOnce : "<<num1<<" "<<num2<<"\n";
        std::cout<<"\n";
    }

    Solution_by_set st;
    for(i = 0; i < vt.size(); i++) {
        st.FindNumsAppearOnce(vt.at(i), &num1, &num2);
        traversevector(vt.at(i));
        std::cout<<"FindNumsAppearOnce : "<<num1<<" "<<num2<<"\n";
        std::cout<<"\n";
    }

    Solution_by_map sp;
    for(i = 0; i < vt.size(); i++) {
        sp.FindNumsAppearOnce(vt.at(i), &num1, &num2);
        traversevector(vt.at(i));
        std::cout<<"FindNumsAppearOnce : "<<num1<<" "<<num2<<"\n";
        std::cout<<"\n";
    }
    return 0;
}
