#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
LC: 39
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。
说明：
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。 
*/

/*
去重复
在搜索的时候，需要设置搜索起点的下标 begin ，由于一个数可以使用多次，下一层的结点从这个搜索起点开始搜索；
在搜索起点 begin 之前的数因为以前的分支搜索过了，所以一定会产生重复。
剪枝提速
如果一个数位搜索起点都不能搜索到结果，那么比它还大的数肯定搜索不到结果，基于这个想法，我们可以对输入数组进行排序，以减少搜索的分支；

排序是为了提高搜索速度，非必要；

搜索问题一般复杂度较高，能剪枝就尽量需要剪枝。把候选数组排个序，遇到一个较大的数，如果以这个数为起点都搜索不到结果，后面的数就更搜索不到结果了。

作者：liweiwei1419
链接：https://leetcode-cn.com/problems/combination-sum/solution/hui-su-suan-fa-jian-zhi-python-dai-ma-java-dai-m-2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
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