#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;
/*
200. Number of Islands

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally
or vertically. You may assume all four edges of the grid are all surrounded by water. 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-islands
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
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