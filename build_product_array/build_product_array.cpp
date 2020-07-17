#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>

/*
Given an array A[0,1,...,n-1], please construct an array B[0,1,...,n-1], where the element B[i]=A[ 0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]. 
You cannot use division. (Note: Provision B[0] = A[1] * A[2] * ... * A[n-1], B[n-1] = A[0] * A[1] * ... * A[n-2];)

Difficulty: 1 star
Finished by self: no
*/

//Time complexity: O(n)
class Solution_by_rules {
public:
    std::vector<int> multiply(const std::vector<int>& A) {
        int i = 0;
        int size = A.size();
        std::vector<int> left(size);//You should initilize the vector elements.
        std::vector<int> right(size);
        left.at(i) = 1;
        right.at(size - 1) = 1;
        for(i = 1; i < size; i++) {
            left.at(i) = left.at(i-1) * A.at(i-1);
            right.at(size - i - 1) = right.at(size - i) * A.at(size - i);
        }
        std::vector<int> vt;
        i = 0;
        for(i = 0; i < size; i++)
            vt.push_back(left.at(i) * right.at(i));//You can save this vector memory.
        return vt;
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
    std::vector<int> vt1 = {4, 5, 6, 1, 2, 3};
    std::vector<int> vt2 = {5, 6, 1, 2, 3, 4};
    std::vector<int> vt3 = {1, 0, 1, 1, 1};
    std::vector<int> vt4 = {1, 1, 1, 0, 1};
    std::vector<int> vt5 = {2, 1};
    std::vector<int> vt6 = {1, 2};
    std::vector<int> vt7 = {1};
    std::vector<std::vector<int>> vt = {vt1, vt2, vt3, vt4, vt5, vt6, vt7};
    Solution_by_rules st;
    unsigned i = 0;
    for(i = 0; i < vt.size(); i++) {
        std::vector<int> result = st.multiply(vt.at(i));
        std::cout<<"Solution_by_rules. multiply list is \n";
        traversevector(result);
        std::cout<<"\n";
    }
    return 0;
}
