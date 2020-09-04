#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
private:
    long long count;
    void helper(vector<int>& nums, int target, vector<long long> &memo) {
        if(target < 0) return;
        if(target == 0) {
            count++;
            return;
        }
        if(memo[target] != -1) 
        {
            count += memo[target];
            count %= INT_MAX;
            return;
        }
        for(int val : nums) {
            if(target - val >= 0) {
                helper(nums, target - val, memo);
            }
        }
    }
public:
    int combinationSum4(vector<int>& nums, int target) {
        //CHECK
        if(nums.size() == 0  && target > 0) return 0;
        if(target == 0) return 1;
        count = 0;
        std::vector<long long> memo(target+1, -1);
        memo[0] = 0;
        for(int i =1; i <= target; i++) {
            count = 0;
            helper(nums, i, memo);
            memo[i] = count;
        }
            
        return count;
    }
};

int main() {
    vector<int> vt = {1, 2, 3};
    Solution sl;
    int res = sl.combinationSum4(vt, 4);
    cout<<"res is "<<res<<"\n";
    return 0;
}