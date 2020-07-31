#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。
说明：
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。 
*/
class Solution {
private:
    std::vector<std::vector<int>> ret;
    //instead of caculating everytime, do it with an input parameter.
    /*int totalsum(vector<int> &path) {
        int sum = 0;
        for(auto it : path) {
            sum += it;
        }
        return sum;
    }*/
    void combination(vector<int>& candidates, int start, vector<int>& path, int target, int currentsum) {
        //terminate case, if start val > target, if path total == target or > target
        if(currentsum == target) {
            ret.emplace_back(path);
            return;
        }
        //backtrack
        //do choice
        //backtrack
        //undo choice
        //if(currentsum > target) return;//merge this judgement with later one.
        for(int i = start; i < candidates.size(); i++) {
            if(currentsum + candidates[i] > target ) continue;
            path.emplace_back(candidates[i]);
            combination(candidates, i, path, target, currentsum+candidates[i]);//plus inside, not outside.
            path.pop_back();
        }

        //return
        return;
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        //check
        ret.clear();
        if(candidates.size() == 0) return ret;
        //path
        vector<int> path;
        path.clear();
        
        //call backtrack
        std::sort(candidates.begin(), candidates.end());
        combination(candidates, 0, path, target, 0);

        //return
        return ret;
    }
};

int main() {

    //Solution sl;
    Solution sl;
    std::vector<int> vt = {2, 3, 6, 7};
    std::vector<std::vector<int>> vs = sl.combinationSum(vt, 7);
    for(auto itt: vs) {
        for(auto it: itt) {
            std::cout<<"["<<it<<"]";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
    return 0;
}