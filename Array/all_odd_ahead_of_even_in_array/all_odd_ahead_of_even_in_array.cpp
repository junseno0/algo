#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <string>
/*
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，
所有的偶数位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。

Enter an integer array and implement a function to adjust the order of the numbers in the array so
that all odd numbers are in the first half of the array, and all even numbers are in the second
half of the array, and the relative relationship between odd and odd, even and even is guaranteed The location remains unchanged.

Difficulty: 1 star
Finished by self: yes
*/

//Time complexity: O(n^2)
//Space complexity: O(1)
class Solution_by_in_place {
public:
    void moveback(std::vector<int> &array, int pos, int n) {
        for(int i = pos+n-1; i >= pos; i--) {
            array[i+1] = array[i]; 
        }
    }
    void reOrderArray(std::vector<int> &array) {
        // oddpos, the pos to insert a odd value
        // pos, the pos traverse
        int oddpos = 0;
        int pos = 0;
        int val = 0;
        //move what, oddpos to pos-1
        //start pos, oddpos, num, pos - oddpos
        //terminate case, pos to size end
        for(pos = 0; pos < array.size(); pos++) {
            //array[pos]&1
            if(array[pos] % 2 == 1) {
                val = array[pos];
                moveback(array, oddpos, pos-oddpos);
                //replaced by array[oddpos++] = val;
                array[oddpos] = val;
                oddpos++;
            }
        }
    }
};

//Time complexity: O(n)
//Space complexity: O(n)
class Solution_by_stl {
public:
    void reOrderArray(std::vector<int> &array) {
        //check
        std::stable_partition(array.begin(), array.end(),
                             [](int val){return val&1;});
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
    std::vector<int> vt1 = {1, 2, 3};
    std::vector<int> vt2 = {1, 3, 3, 4, 5, 6};
    std::vector<int> vt3 = {364,637,341,406,747,995,234,971,571,219,993,407,
        416,366,315,301,601,650,418,355,460,505,360,965,516,648,727,667,465,849,
        455,181,486,149,588,233,144,174,557,67,746,550,474,162,268,142,463,221,882,
        576,604,739,288,569,256,936,275,401,497,82,935,983,583,523,697,478,147,795,
        380,973,958,115,773,870,259,655,446,863,735,784,3,671,433,630,425,930,64,266,
        235,187,284,665,874,80,45,848,38,811,267,575};
    
    std::vector<std::vector<int>> vt = {vt1, vt2, vt3};
    unsigned int i = 0;

    Solution_by_in_place ss;
    for(i = 0; i < vt.size(); i++) {
        vt = {vt1, vt2, vt3};
        std::cout<<"Solution_by_in_place. Before reodering array."<<"\n";
        traversevector(vt.at(i));
        ss.reOrderArray(vt.at(i));
        std::cout<<"Solution_by_in_place. After reodering array."<<"\n";
        traversevector(vt.at(i));
    }

    Solution_by_stl sl;
    for(i = 0; i < vt.size(); i++) {
        vt = {vt1, vt2, vt3};
        std::cout<<"Solution_by_stl. Before reodering array."<<"\n";
        traversevector(vt.at(i));
        sl.reOrderArray(vt.at(i));
        std::cout<<"Solution_by_stl. After reodering array."<<"\n";
        traversevector(vt.at(i));
    }
    return 0;
}
