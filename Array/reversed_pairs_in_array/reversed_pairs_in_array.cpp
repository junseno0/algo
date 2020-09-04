#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <string>
/*
For two numbers in the array, if the first number is greater than the following number, the two numbers form a reverse pair.
Enter an array and find the total number P of reverse pairs in this array. And output the result of P modulo 1000000007. That is to output P%1000000007

Difficulty: 2 star
Finished by self: no
*/

//Time complexity: average: O(nlogn)
//Space complexity: average: O(1)
class Solution {
public:
    void mergeSort(std::vector<int> &data, int left, int mid, int right, int &count) {
        if(data.size() <= 1) return;
        //copy vector
        std::vector<int> aux(data);
        //for(int i = left; i <= right; i++) {
            //aux.push_back(data.at(i));
        //}
        //merge with sz and i
        int i = left;
        int j = mid + 1;
        /*
        for(int k = left; k <= right; k++) {
            if(i > mid) {
                data.at(k) = aux.at(j);
                j++;
            } else if (j > right) {
                data.at(k) = aux.at(i);
                i++;
            } else if (aux.at(i) <= aux.at(j)) {
                data.at(k) = aux.at(i);
                i++;
            } else if (aux.at(i) > aux.at(j))  {
                data.at(k) = aux.at(j);
                j++;
                count += (mid - i + 1);
                count %= %1000000007;
            }
        }
        */
        int k = left;
        while(i <= mid && j <= right) {
            if (aux.at(i) > aux.at(j)) {
                data.at(k++) = aux.at(j++);
                count = (count + mid - i + 1)%1000000007;
            } else {
                data.at(k++) = aux.at(i++);
            }
        }
        while(i <= mid) {
            data.at(k++) = aux.at(i++);
        }
        while(j <= right) {
            data.at(k++) = aux.at(j++);
        }
    }
    int InversePairs(std::vector<int> &data) {
        //check
        if(data.size() <= 0) return 0;
        //merge sort
        //if left > right, then the ones after left all > right, save thte count
        //STL? no
        //2, 4, 8,..., until 2 * segment > size
        //sort all segments, 2 + 2 + 2 ... > size, 4 + 4 + 4 ... > size, etc...
        // another vector ? how to use ?
        int count = 0;
        int n = data.size();
        for(int sz = 1; sz <= n; sz *= 2) {
            for(int i = 0; i + sz < n; i += 2 * sz) {
                // i + sz -1 : be valid, i + sz : be valid
                mergeSort(data, i, i + sz - 1, std::min(i + 2 * sz - 1, n - 1), count);
            }
        }
        //return
        return count%1000000007;
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
    std::vector<int> vt1 = {1, 3, 321};
    std::vector<int> vt2 = {1, 3, 3, 4, 5, 6};
    std::vector<int> vt3 = {364,637,341,406,747,995,234,971,571,219,993,407,
        416,366,315,301,601,650,418,355,460,505,360,965,516,648,727,667,465,849,
        455,181,486,149,588,233,144,174,557,67,746,550,474,162,268,142,463,221,882,
        576,604,739,288,569,256,936,275,401,497,82,935,983,583,523,697,478,147,795,
        380,973,958,115,773,870,259,655,446,863,735,784,3,671,433,630,425,930,64,266,
        235,187,284,665,874,80,45,848,38,811,267,575};
    
    std::vector<std::vector<int>> vt = {vt1, vt2, vt3};
    unsigned int i = 0;
    int count = 0;

    Solution ss;
    for(i = 0; i < vt.size(); i++) {
        count = ss.InversePairs(vt.at(i));
        traversevector(vt.at(i));
        std::cout<<"Solution_by_binary_search_stl. GetNumberOfK : "<<count<<"\n";
        std::cout<<"\n";
    }
    return 0;
}
