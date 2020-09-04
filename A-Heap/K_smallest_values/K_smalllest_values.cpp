#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <vector>
using namespace std;

/*
JZ29 最小的K个数
*/

class Solution {
private:
    int partition(vector<int> &input, int lo, int hi) {
        //by random select
        int anchor =  input[lo];
        while(lo < hi) {
            while((lo < hi) && anchor <= input[hi]) hi--;
            input[lo] = input[hi];
            while((lo <hi) && anchor > input[lo]) lo++;
            input[hi] = input[lo];
        }
        input[lo] = anchor;
        return lo;
    }
    void quicksort(std::vector<int> &input, int left, int right) {
        //pick first as anchor
        //sort left part and right part
        if( right - left < 2) return;
        int mid = partition(input, left, right);
        quicksort(input, left, mid-1);
        quicksort(input, mid+1, right);
        return;
    }
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        std::vector<int> vt;
        if(input.size() < k || k <= 0) return vt;
        quicksort(input, 0, input.size()-1);
        vt.assign(input.begin(), input.begin()+k);
        return vt;
    }
};
int main()
{
    std::vector<int> vt = {5, 3, 8, 12, 7, 2};
    Solution sl;
    std::vector<int> res = sl.GetLeastNumbers_Solution(vt, 3);
    std::cout<<"GetLeastNumbers_Solution in {5, 3, 8, 12, 7, 2}, max sum : ";
    for(auto it : res) {
        std::cout<<"["<<it<<"] ";
    }
    return 0;
}
