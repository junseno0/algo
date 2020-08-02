#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
417. Pacific Atlantic Water Flow

Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent,
the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.
Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.
Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/pacific-atlantic-water-flow
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
* This solution not work well. It kills time.
*/
class Solution_v1 {
private:
    int m;
    int n;
    vector<vector<int>> dp = { {0, -1}, {0,  1},{-1, 0}, {1, 0}};
    bool pacific;
    bool atlantic;
    vector<vector<bool>> visited;
    std::vector<std::vector<int>> ret;
    bool inArea(int i, int j) {
        if(i >= 0 && i < m && j >= 0 && j < n) return true;
        return false;
    }
    void dfs(vector<vector<int>>& matrix, int x, int y) {
        int newx;
        int newy;
        if(atlantic && pacific) return;
        visited[x][y] = true;
        //for all directions, search pacific and atlantic, if yes, set bool
        for(int dir = 0; dir < 4; dir++) {
            newx = x + dp[dir][0];
            newy = y + dp[dir][1];
            if(dir == 0)
                std::cout<<"dir: up\n";
            else if(dir == 1)
                std::cout<<"dir: donw\n";
            else if(dir == 2)
                std::cout<<"dir: left\n";
            else if(dir == 3)
                std::cout<<"dir: right\n";
            if(inArea(newx, newy) == false) {
                std::cout<<"not in area. newx: "<<newx<<" newy: "<<newy<<"\n";
                if(newx == -1 || newy == -1) pacific = true;
                if(newx == m || newy == n) atlantic = true;
                continue;//not return
            }
            if(matrix[newx][newy] > matrix[x][y] || visited[newx][newy] == true) continue;//not return
            std::cout<<"To dfs. new x: "<<newx<<" new y: "<<newy<<" val: "<<matrix[newx][newy]<<"\n";
            dfs(matrix, newx, newy);
        }

        return;
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        //check
        if(matrix.size() == 0) return ret;
        m = matrix.size();
        n = matrix[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        //backtrack
        for(int i =  0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                //i = 1;
                //j = 3;
                pacific = false;
                atlantic = false;
                //NOT use auto for two loop, it sucks.
                for(int x = 0; x< m; x++)
                    for(int y = 0; y < n; y++)
                        visited[x][y] = false;
                dfs(matrix, i, j);
                if(pacific && atlantic){
                    std::vector<int> path;
                    path.clear();
                    path.push_back(i);
                    path.push_back(j);
                    ret.push_back(path);
                }
            }
        }
        //return
        return ret;
    }
};

class Solution_v2 {
private:
    int m;
    int n;
    vector<vector<int>> dp = { {0, -1}, {0,  1},{-1, 0}, {1, 0}};
    vector<vector<bool>> pacific;
    vector<vector<bool>> atlantic;
    std::vector<std::vector<int>> ret;
    bool inArea(int i, int j) {
        if(i >= 0 && i < m && j >= 0 && j < n) return true;
        return false;
    }
    void dfs(vector<vector<int>>& matrix, int x, int y, bool pflag) {
        int newx;
        int newy;
        if(pflag)
            pacific[x][y] = true;
        else
            atlantic[x][y] = true;
        //for all directions, search pacific and atlantic, if yes, set bool
        for(int dir = 0; dir < 4; dir++) {
            newx = x + dp[dir][0];
            newy = y + dp[dir][1];
            if(inArea(newx, newy) == false ||
                matrix[newx][newy] < matrix[x][y]) continue;//not return
            if(pflag && pacific[newx][newy]) continue;
            if(!pflag && atlantic[newx][newy]) continue;
            dfs(matrix, newx, newy, pflag);
        }

        return;
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        //check
        if(matrix.size() == 0) return ret;
        m = matrix.size();
        n = matrix[0].size();
        pacific = vector<vector<bool>>(m, vector<bool>(n, false));
        atlantic = vector<vector<bool>>(m, vector<bool>(n, false));
        
        //backtrack

        //from up and down, pacific and atlantic
        for(int i = 0; i < m; i++) {
            dfs(matrix, i, 0, true);//from up
            dfs(matrix, i, n-1, false);//from down
        }
        //from left and right, pacific and atlantic
        for(int j =  0; j < n; j++) {
            dfs(matrix, 0, j, true);
            dfs(matrix, m-1, j, false);
        }
        
        //check pacific set and atlantic set
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(pacific[i][j] && atlantic[i][j]) {
                    vector<int> path;
                    path.push_back(i);
                    path.push_back(j);
                    ret.push_back(path);
                }
            }
        }
        //return
        return ret;
    }
};

class Solution_v3 {
private:
    int m;
    int n;
    vector<vector<int>> dp = { {0, -1}, {0,  1},{-1, 0}, {1, 0}};
    vector<vector<bool>> pacific;
    vector<vector<bool>> atlantic;
    std::vector<std::vector<int>> ret;
    bool inArea(int i, int j) {
        if(i >= 0 && i < m && j >= 0 && j < n) return true;
        return false;
    }
    void dfs(vector<vector<int>>& matrix, int x, int y, bool pflag) {
        int newx;
        int newy;
        if(pflag)
            pacific[x][y] = true;
        else
            atlantic[x][y] = true;
        //for all directions, search pacific and atlantic, if yes, set bool
        std::queue<pair<int, int>> qt;
        qt.push({x, y});
        while(!qt.empty()) {
            pair<int, int> rc = qt.front();
            qt.pop();
            if(pflag) pacific[rc.first][rc.second] = true;
            else atlantic[rc.first][rc.second] = true;
            for(int dir = 0; dir < 4; dir++) {
                newx = rc.first + dp[dir][0];
                newy = rc.second + dp[dir][1];
                if(inArea(newx, newy) == false ||
                    matrix[newx][newy] < matrix[rc.first][rc.second]) continue;//not return
                if(pflag && pacific[newx][newy]) continue;
                if(!pflag && atlantic[newx][newy]) continue;
                qt.push({newx, newy});
                if(pflag) pacific[newx][newy] = true;
                else atlantic[newx][newy] = true;
            }
        }

        return;
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        //check
        if(matrix.size() == 0) return ret;
        m = matrix.size();
        n = matrix[0].size();
        pacific = vector<vector<bool>>(m, vector<bool>(n, false));
        atlantic = vector<vector<bool>>(m, vector<bool>(n, false));
        
        //backtrack

        //from up and down, pacific and atlantic
        for(int i = 0; i < m; i++) {
            dfs(matrix, i, 0, true);//from up
            dfs(matrix, i, n-1, false);//from down
        }
        //from left and right, pacific and atlantic
        for(int j =  0; j < n; j++) {
            dfs(matrix, 0, j, true);
            dfs(matrix, m-1, j, false);
        }
        
        //check pacific set and atlantic set
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(pacific[i][j] && atlantic[i][j]) {
                    ret.push_back(vector<int>{i, j});//trick
                }
            }
        }
        //return
        return ret;
    }
};

/*
构建一个状态矩阵：
用第一个bit存储太平洋是否能达到此点
用第二个bit存储大西洋是否能达到此点
最终查询点状态为3（二进制为11）的点即可。
https://leetcode-cn.com/problems/pacific-atlantic-water-flow/solution/c-yan-du-you-xian-bian-li-by-da-li-wang/
*/
/*
class Solution {
public:
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool valid(int r, int c, int R, int C) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<vector<int> > res;
        if (matrix.empty()) return res;
        int R = matrix.size();
        int C = matrix[0].size();
        vector<vector<int> > status(R, vector<int>(C, 0));
        queue<pair<int, int> > q;
        for (int i = 0; i < R; ++i) {
            q.push({i, 0});
            status[i][0] |= 1;
            q.push({i, C - 1});
            status[i][C - 1] |= 2;
        }
        for (int i = 0; i < C; ++i) {
            q.push({0, i});
            status[0][i] |= 1;
            q.push({R - 1, i});
            status[R - 1][i] |= 2;
        }
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int r = p.first + dirs[i][0];
                int c = p.second + dirs[i][1];
                if (valid(r, c, R, C) && matrix[r][c] >= matrix[p.first][p.second]) {
                    if (status[r][c] != status[p.first][p.second]) {
                        status[r][c] |= status[p.first][p.second];
                        q.push({r, c});
                    }
                }
            }
        }
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (status[i][j] == 3) {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }
};
*/

int main() {

    //Solution sl;
    Solution_v2 sl;
    std::vector<std::vector<int>> vt1 = 
    {{1,2,2,3,5}, 
     {3,2,3,4,4}, 
     {2,4,5,3,1}, 
     {6,7,1,4,5},
     {5,1,1,2,4}};
    //[[3,3,3,3,3,3],[3,0,3,3,0,3],[3,3,3,3,3,3]]
    std::vector<std::vector<int>> vt2 = 
    {{3,3,3,3,3,3}, 
     {3,0,3,3,0,3}, 
     {3,3,3,3,3,3}};
    //[[1,1],[1,1],[1,1]]
    sl.pacificAtlantic(vt2);
    return 0;
}