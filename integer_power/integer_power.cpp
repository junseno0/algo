#include <iostream>

/*
给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
保证base和exponent不同时为0

Given a floating-point base of type double and an integer exponent of type int. Find the exponent power of base.
Ensure that base and exponent are not 0 at the same time

Difficulty: 1 star
Finished by self: yes
*/

//Time complexity: O(logn)
//Space complexity: O(1)
class Solution_by_recursion {
public:
    double Power(double base, int exponent) {
        if (base == 0) return 0;
        if(exponent < 0) {
            base = 1/base;
            exponent = -1 * exponent;
        }
        if(exponent == 1)
            return base;
        else if (exponent == 0)
            return 1;
        if(exponent & 1)
            return Power(base, exponent/2) * Power(base, exponent/2) * base;
        else 
            return Power(base, exponent/2) * Power(base, exponent/2);
    }
};

class Solution_by_iteration {
public:
    double Power(double base, int exponent) {
        if (base == 0) return 0;
        if(exponent < 0) {
            base = 1/base;
            exponent = -1 * exponent;
        }
        if(exponent == 1)
            return base;
        else if (exponent == 0)
            return 1;
        double x = base;
        double ret = base;
        while( exponent > 0 ) {
            x = x * x;
            exponent = exponent >> 1;
            if(exponent & 1){
                ret = ret * x;
            }
        }
        return ret;
    }  
};

int main()
{
    Solution_by_recursion sr;
    double value = -2;
    for(value = -2; value < 2; value++)
        std::cout<<"Power of value "<<value<<" is "<<sr.Power(value, 5)<<"\n";
    Solution_by_iteration si;
    for(value = -2; value < 2; value++)
        std::cout<<"Power of value "<<value<<" is "<<si.Power(value, 5)<<"\n";    
    return 0;
}
