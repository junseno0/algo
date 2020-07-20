#include <iostream>
#include <vector>
#include <stack>
/*
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。
假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，
序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
（注意：这两个序列的长度是相等的）

Enter two integer sequences. The first sequence indicates the order in which the stack is pushed.
Please judge whether the second sequence is the pop-up order of the stack.
Assume that all numbers pushed onto the stack are not equal.
For example, the sequence 1, 2, 3, 4, 5 is the pushing order of a certain stack,
and the sequence 4, 5, 3, 2, 1 is a pop sequence corresponding to the pushing sequence,
but 4, 3, 5, 1, 2 It cannot be the pop sequence of the push sequence. (Note: the lengths of these two sequences are equal)

Difficulty: 1 star
Finished by self: no
*/

/*
链接：https://www.nowcoder.com/questionTerminal/d77d11405cc7470d82554cb392585106?answerType=1&f=discussion
来源：牛客网

* 直接模拟即可。因为弹出之前的值都会先入栈，所以这里用个栈来辅助。
* 1,初始化：用指针i指向pushV的第一个位置， 指针j指向popV的第一个位置
* 2,如果pushV[i] != popV[j]， 那么应该将pushV[i]放入栈中， ++i
* 3,否则，pushV[i]==popV[j], 说明这个元素是放入栈中立马弹出，所以，++i, ++j，然后应该检查popV[j]
*     与栈顶元素是否相等，如果相等，++j, 并且弹出栈顶元素
* 4，重复2，3， 如果i==pushV.size(), 说明入栈序列访问完，此时检查栈是否为空，如果为空，说明匹配，斗则不匹配。
*/

class Solution_v1 {
public:
    bool IsPopOrder(std::vector<int> pushV,std::vector<int> popV) {
        std::stack<int> st;
        int pushcount = 0;
        int popcount = 0;
        while(pushcount < pushV.size()) {
            st.push(pushV[pushcount]);
            pushcount++;
            //if not equal, keep push
            if(st.top() != popV[popcount]) {
                st.push(pushV[pushcount]);
                pushcount++;
            }
            //while equal, pop
            //if st empty, popV just be max
            while(!st.empty() && st.top() == popV[popcount]) {
                st.pop();
                popcount++;
            }
            
        }
        return st.empty();
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
    std::vector<int> pushv = {1, 2, 3, 4, 5};
    std::vector<int> popv1 = {4, 3, 5, 1, 2};
    std::vector<int> popv2 = {4, 5, 3, 2, 1};
    std::vector<std::vector<int>> vt = {popv1, popv2};
    Solution_v1 s1;
    bool flag = false;
    unsigned int i = 0;
    for(i = 0; i < vt.size(); i++) {
        flag = s1.IsPopOrder(pushv, vt[i]);
        traversevector(vt[i]);
        std::cout<<"Solution_v1. IsPopOrder : "<<flag<<"\n";
    }

    return 0;
}
