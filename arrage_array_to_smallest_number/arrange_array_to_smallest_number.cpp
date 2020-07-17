#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <string>
/*
Enter an array of positive integers, concatenate all the numbers in the array into a number,
and print the smallest of all the numbers that can be concatenated. 
For example, if you input the array {3, 32, 321}, the smallest number that can be arranged by these three numbers is 321323.

Difficulty: 1 star
Finished by self: no
*/

//Time complexity: average: O(nlogn)
//Space complexity: average: O(1)
//STL sort is available
class Solution_by_string_trick {
public:
    std::string PrintMinNumber(std::vector<int> numbers) {
        //check
        std::string ret = "";
        if(numbers.size() == 0) return ret;
        //int to string
        std::vector<std::string> st;
        for(unsigned int i = 0; i < numbers.size(); i++) {
            st.push_back(std::to_string(numbers.at(i)));
        }
        //pass by lambda
        auto comp = [](std::string a, std::string b){return a + b < b + a;};
        std::sort(st.begin(), st.end(), comp);
        
        for(auto it : st) ret += it;
        return ret;
    }
};

class Solution_by_string_trick_v2 {
public:
    std::string PrintMinNumber(std::vector<int> numbers) {
        //check
        std::string ret = "";
        if(numbers.size() == 0) return ret;
        //int to string
        std::vector<std::string> st;
        for(unsigned int i = 0; i < numbers.size(); i++) {
            st.push_back(std::to_string(numbers.at(i)));
        }
        //pass by function object
        struct comp{
            bool operator()(std::string a, std::string b){
                return a + b < b + a;
            }
        };
        std::sort(st.begin(), st.end(), comp());
        
        for(auto it : st) ret += it;
        return ret;
    }
};

class Solution_by_string_trick_v3 {
public:
    //pass by function pointer
    static bool comp(std::string a, std::string b) {
        return a + b < b + a;
    }
    std::string PrintMinNumber(std::vector<int> numbers) {
        //check
        std::string ret = "";
        if(numbers.size() == 0) return ret;
        //int to string
        std::vector<std::string> st;
        for(unsigned int i = 0; i < numbers.size(); i++) {
            st.push_back(std::to_string(numbers.at(i)));
        }
        std::sort(st.begin(), st.end(), comp);
        
        for(auto it : st) ret += it;
        return ret;
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
    std::vector<int> vt1 = {32, 3, 321};
    std::vector<int> vt2 = {5, 6, 1, 1, 3, 3};
    std::vector<std::vector<int>> vt = {vt1, vt2};
    unsigned int i = 0;
    std::string str;
    Solution_by_string_trick_v3 st;
    for(i = 0; i < vt.size(); i++) {
        str = st.PrintMinNumber(vt.at(i));
        traversevector(vt.at(i));
        std::cout<<"PrintMinNumber. string : "<<str<<"\n";
        std::cout<<"\n";
    }

    return 0;
}
