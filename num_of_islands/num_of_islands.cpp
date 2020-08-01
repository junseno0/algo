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
class Solution_DFS {
private:
    vector<vector<bool>> visited;
    int m;
    int n;
    int dp[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};//up, right, down, left direction.
    // for i = 0 to 3, grid[startx+dp[i][0]][starty+dp[i][1]], grid[x+dp[i][0]][y+dp[i[1]]]....
    bool available(vector<vector<char>>& grid, int startx, int starty) {
        if(startx >= 0 && startx < m && starty >= 0 && starty < n &&
            visited[startx][starty] == false && grid[startx][starty] == '1')
            return true;
        return false;
    }
    void helper(vector<vector<char>>& grid, int startx, int starty) {
        //start from x, y
        //probe next available direction with for
        //do choice
        //backtrack
        visited[startx][starty] = true;
        for(int dir = 0; dir < 4; dir++) {
            //terminate case included here.
            if(available(grid, startx+dp[dir][0], starty+dp[dir][1]) == false) continue;
            helper(grid, startx+dp[dir][0], starty+dp[dir][1]);
        }
        //no need to undo choice.
        return;
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        //check
        if(grid.size() == 0) return 0;

        //helper
        int count = 0;
        m = grid.size();
        n = grid[0].size();
        //Be aware of m and n indication.
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(available(grid, i, j)) {
                    count++;
                    helper(grid, i, j);
                }
            }
        }

        //return land count
        return count;
    }
};

class Solution_BFS {
private:
    vector<vector<bool>> visited;
    int m;
    int n;
    queue<pair<int, int>> qt;
    int dp[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};//up, right, down, left direction.
    // for i = 0 to 3, grid[startx+dp[i][0]][starty+dp[i][1]], grid[x+dp[i][0]][y+dp[i[1]]]....
    bool available(vector<vector<char>>& grid, int startx, int starty) {
        if(startx >= 0 && startx < m && starty >= 0 && starty < n &&
            visited[startx][starty] == false && grid[startx][starty] == '1')
            return true;
        return false;
    }
    void helper(vector<vector<char>>& grid, int startx, int starty) {
        qt.push({startx, starty});
        int newx = 0;
        int newy = 0;
        while(!qt.empty()) {
            pair<int, int> rc = qt.front();
            qt.pop();
            visited[rc.first][rc.second] = true;
            for(int dir = 0; dir < 4; dir++) {
                //terminate case included here.
                newx = rc.first+dp[dir][0];
                newy = rc.second+dp[dir][1];
                if(available(grid, newx, newy) == false) continue;
                qt.push({newx, newy});
                visited[newx][newy] = true;
            }
    }
        return;
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        //check
        if(grid.size() == 0) return 0;

        //helper
        int count = 0;
        m = grid.size();
        n = grid[0].size();
        //Be aware of m and n indication.
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(available(grid, i, j)) {
                    count++;
                    helper(grid, i, j);
                }
            }
        }

        //return land count
        return count;
    }
};

class Solution_BSF_v2 {
private:
    int m;
    int n;
    queue<pair<int, int>> qt;
    int dp[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};//up, right, down, left direction.
    // for i = 0 to 3, grid[startx+dp[i][0]][starty+dp[i][1]], grid[x+dp[i][0]][y+dp[i[1]]]....
    bool available(vector<vector<char>>& grid, int startx, int starty) {
        if(startx >= 0 && startx < m && starty >= 0 && starty < n &&
            grid[startx][starty] == '1')
            return true;
        return false;
    }
    void helper(vector<vector<char>>& grid, int startx, int starty) {
        qt.push({startx, starty});
        int newx = 0;
        int newy = 0;
        while(!qt.empty()) {
            pair<int, int> rc = qt.front();
            qt.pop();
            grid[rc.first][rc.second] = '0';
            for(int dir = 0; dir < 4; dir++) {
                //terminate case included here.
                newx = rc.first+dp[dir][0];
                newy = rc.second+dp[dir][1];
                if(available(grid, newx, newy) == false) continue;
                qt.push({newx, newy});
                grid[newx][newy] = '0';
            }
    }
        return;
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        //check
        if(grid.size() == 0) return 0;

        //helper
        int count = 0;
        m = grid.size();
        n = grid[0].size();
        //Be aware of m and n indication.
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == '1') {
                    count++;
                    helper(grid, i, j);
                }
            }
        }
        //return land count
        return count;
    }
};

int main() {

    //Solution sl;
    Solution_DFS sl;
    std::vector<std::vector<char>> vt1 = 
    {{'1','1','1','1','0'}, 
     {'1','1','0','1','0'}, 
     {'1','1','0','0','0'}, 
     {'0','0','0','0','0'}};
    std::vector<std::vector<char>> vt2 = 
    {{'1','1','0','0','0'}, 
     {'1','1','0','0','0'}, 
     {'0','0','0','1','0'}, 
     {'0','0','0','0','1'}};
    int count = 0;
    count = sl.numIslands(vt1);
    std::cout<<"num of islands : "<<count<<"\n";
    count = sl.numIslands(vt2);
    std::cout<<"num of islands : "<<count<<"\n";
    return 0;
}