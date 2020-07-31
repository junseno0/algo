#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
public void backtrack(路径，选择列表){
    if(满足结束条件){
        result.add(结果);
    }
    for(选择：选择列表){
        做出选择;
        backtrack(路径，选择列表);
        撤销选择;
    }
}

其中最关键的点就是：在递归之前做选择，在递归之后撤销选择。
由于本题需要返回所有不重复的全排列，有限制条件，所以需要进行剪枝。这里第一步先要给数组进行排序。
首先，先要给nums进行排序，这样的做目的是方便剪枝
其次，我们已经选择过的不需要再放进去了
接下来，如果当前节点与它的前一个节点一样，并且，前一个节点刚被撤消，也就是状态为未被访问，
那么就会出现重复，当前就需要剪枝。

作者：ming-zhi-shan-you--m9RfkvKDad
链接：https://leetcode-cn.com/problems/permutations-ii/solution/47-quan-pai-lie-ii-by-ming-zhi-shan-you-m9rfkvkdad/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

/*
* 参考liweiwei的题解。https://leetcode-cn.com/problems/permutations-ii/solution/hui-su-suan-fa-python-dai-ma-java-dai-ma-by-liwe-2/
*/
class Solution {
public:
    //ret
    vector<vector<int>> ret;
    void  permute(vector<int>& nums, int start, vector<int>& path, vector<bool> &visited) {
        //terminate case
        if(path.size() == nums.size()) {
            ret.emplace_back(path);
            return;
        }
        //backtrack
        //do choice
        //backtrack
        //undo choice
        for(int i = start; i < nums.size(); i++) {
            if(i >= 1 && visited[i-1] == false && nums[i-1] == nums[i]) continue;//trick!
            if(visited[i] == false) {
                path.emplace_back(nums[i]);
                visited[i] = true;
            } else {
                continue;
            }
            permute(nums, start, path, visited);
            path.pop_back();
            visited[i] = false;
        }
        return;
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        //check
        ret.clear();
        if(nums.size() == 0) return ret;
        //path
        vector<int> path;
        vector<bool> visited(nums.size(), false);
        //call permute
        std::sort(nums.begin(), nums.end());
        permute(nums, 0, path, visited);
        return ret;
    }
};

int main() {

    //Solution sl;
    Solution_v1 sl;
    std::string s = "aab";
    std::vector<std::vector<std::string>> vs = sl.partition(s);
    for(auto itt: vs) {
        for(auto it: itt) {
            std::cout<<"["<<it<<"]";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
    return 0;
}