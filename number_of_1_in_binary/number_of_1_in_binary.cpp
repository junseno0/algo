#include <iostream>

/*
输入一个整数，输出该数32位二进制表示中1的个数。其中负数用补码表示。

Enter an integer and output the number of 1s in the 32-bit binary representation of the number.
The negative number is represented by complement.

Difficulty: 1 star
Finished by self: yes
*/

//Time complexity: O(32)
//Space complexity: O(1)
class Solution_by_move_bit {
public:
     int  NumberOf1(int n) {
         int count = 0;
         for(int i = 0; i < 32; i++) {
             if(n & 1) count++;
             n = n >> 1;
         }
         return count;
     }
};

class Solution_by_trick {
public:
     int  NumberOf1(int n) {
         int count = 0;
         while(n != 0) {
             count++;
             n = n & (n - 1);
         }
         return count;
     }
};

#include <bitset>
int main()
{
    Solution_by_move_bit sv;
    int value = -5;
    for(value = -5; value < 10; value++)
        std::cout<<"Number of 1 in binary "<<std::bitset<32>(value)<<" for value "<<value<<" is "<<sv.NumberOf1(value)<<"\n";
    Solution_by_trick st;
    for(value = -5; value < 10; value++)
        std::cout<<"Number of 1 in binary "<<std::bitset<32>(value)<<" for value "<<value<<" is "<<st.NumberOf1(value)<<"\n";        
    return 0;
}
