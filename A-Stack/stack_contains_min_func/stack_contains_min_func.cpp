#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

/*
定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间复杂度应为O（1））。

To define the data structure of the stack, please implement a min function in this type
that can get the smallest element contained in the stack (time complexity should be O(1)).

Difficulty: 1 star
Finished by self: no
*/

class Solution_v1 {
public:
    std::vector<int> vt;
    int xmin;
    Solution_v1(){xmin = INT_MAX;};
    void push(int value) {
        vt.push_back(value);
        if(value < xmin) xmin = value;
    }
    void pop() {
        int back = vt.back();
        vt.pop_back();
        // std::min VS std::min_element
        if(back == xmin) xmin = *std::min_element(vt.begin(), vt.end());
    }
    int top() {
        return vt[vt.size()-1];
    }
    int min() {
        return xmin;
    }
};

class Solution_two_stack {
public:
    std::stack<int> st;
    std::stack<int> st_min;
    int xmin;
    Solution_two_stack(){xmin = INT_MAX;};
    void push(int value) {
        st.push(value);
        if(value < xmin) xmin = value;
        st_min.push(xmin);
    }
    void pop() {
        st.pop();
        st_min.pop();
    }
    int top() {
        return st.top();
    }
    int min() {
        return st_min.top();
    }
};

int main()
{
    //Solution_v1 s1;
    Solution_two_stack s1;
    s1.push(4);
    std::cout<<"push 4. "<<" ";
    s1.push(2);
    std::cout<<"push 2. min: "<<s1.min()<<". ";
    s1.push(3);
    std::cout<<"push 3. min: "<<s1.min()<<". ";
    s1.push(1);
    std::cout<<"push 1. min: "<<s1.min()<<". ";
    s1.pop();
    std::cout<<"pop. min: "<<s1.min()<<". ";

    return 0;
}
