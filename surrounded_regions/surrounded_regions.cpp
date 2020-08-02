#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
130. Surrounded Regions

Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:

X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/surrounded-regions
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution_DFS {
private:
    int m;
    int n;
    bool linkToBoard;
    vector<vector<bool>> visited;
    vector<pair<int, int>> ret;
    vector<vector<int>> dp = { {0, -1}, {0,  1},{-1, 0}, {1, 0}};
    bool inArea(int x, int y) {
        if(x >= 0 && x < m && y >= 0 && y < n) return true;
        return false;
    }
    void dfs(vector<vector<char>>& board, int x, int y) {
        visited[x][y] = true;
        ret.push_back(make_pair(x, y));
        if(x == 0 || x == m - 1 || y == 0 || y == n - 1) linkToBoard = true;
        int newx;
        int newy;
        for(int dir = 0; dir < 4; dir++) {
            newx = x+dp[dir][0];
            newy = y+dp[dir][1];
            if(inArea(newx, newy) && visited[newx][newy] == false && board[newx][newy] != 'X') {
                dfs(board, newx, newy);
            }
        }
        return;
    }
public:
    void solve(vector<vector<char>>& board) {
        if(board.size() == 0) return;
        m = board.size();
        n = board[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n, 0));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == 'O' && !visited[i][j]) {
                    linkToBoard = false;
                    ret.clear();
                    dfs(board, i, j);
                    if(linkToBoard == false) {
                        for(int i = 0; i < ret.size(); i++) {
                            pair<int, int> rc = ret[i];
                            board[rc.first][rc.second] = 'X';
                        }
                    }
                }
            }
        }
    }
};

/*
1，在DFS开始的地方作终止判断，不在递归调用的时候作判断
2，将for循环改成直接多次调用
3，性能依旧不足，因为是从内向外寻找的，与太平洋大西洋洋流问题一致
*/
class Solution_DFS_v2 {
private:
    int m;
    int n;
    bool linkToBoard;
    vector<vector<bool>> visited;
    vector<pair<int, int>> ret;
    void dfs(vector<vector<char>>& board, int x, int y) {
        if(x < 0 || x >= m || y < 0 || y >= n ||
            visited[x][y]  || board[x][y] == 'X') return;
        visited[x][y] = true;
        ret.push_back(make_pair(x, y));
        if(x == 0 || x == m - 1 || y == 0 || y == n - 1) linkToBoard = true;
        visited[x][y] = true;
        dfs(board, x + 0, y - 1);
        dfs(board, x + 0, y + 1);
        dfs(board, x - 1, y + 0);
        dfs(board, x + 1, y + 0);

        return;
    }
public:
    void solve(vector<vector<char>>& board) {
        if(board.size() == 0) return;
        m = board.size();
        n = board[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n, 0));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == 'O' && !visited[i][j]) {
                    linkToBoard = false;
                    ret.clear();
                    dfs(board, i, j);
                    if(linkToBoard == false) {
                        for(int i = 0; i < ret.size(); i++) {
                            pair<int, int> rc = ret[i];
                            board[rc.first][rc.second] = 'X';
                        }
                    }
                }
            }
        }
    }
};

class Solution_BFS {
private:
    int m;
    int n;
    bool linkToBoard;
    vector<vector<bool>> visited;
    vector<pair<int, int>> ret;
    vector<vector<int>> dp = { {0, -1}, {0,  1},{-1, 0}, {1, 0}};
    bool inArea(int x, int y) {
        if(x >= 0 && x < m && y >= 0 && y < n) return true;
        return false;
    }
    void dfs(vector<vector<char>>& board, int x, int y) {
        visited[x][y] = true;
        ret.push_back(make_pair(x, y));
        if(x == 0 || x == m - 1 || y == 0 || y == n - 1) linkToBoard = true;
        int newx;
        int newy;
        std::queue<pair<int, int>> qt;
        qt.push(make_pair(x, y));
        visited[x][y] = true;
        while(!qt.empty()) {
            std::pair<int, int> rc = qt.front();
            qt.pop();
            for(int dir = 0; dir < 4; dir++) {
                newx = rc.first+dp[dir][0];
                newy = rc.second+dp[dir][1];
                if(inArea(newx, newy) && visited[newx][newy] == false && board[newx][newy] != 'X') {
                    qt.push(make_pair(newx, newy));
                    visited[newx][newy] = true;
                    if(newx == 0 || newx == m - 1 || newy == 0 || newy == n - 1) linkToBoard = true;
                    ret.push_back(make_pair(newx, newy));
                }
            }
        }
        return;
    }
public:
    void solve(vector<vector<char>>& board) {
        if(board.size() == 0) return;
        m = board.size();
        n = board[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n, 0));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == 'O' && !visited[i][j]) {
                    linkToBoard = false;
                    ret.clear();
                    dfs(board, i, j);
                    if(linkToBoard == false) {
                        for(int i = 0; i < ret.size(); i++) {
                            pair<int, int> rc = ret[i];
                            board[rc.first][rc.second] = 'X';
                        }
                    }
                }
            }
        }
    }
};

/*参考该题解，巧妙利用标记的手法与逆向思维的方式解决*/
/*
class Solution {
public:
    void dfs(vector<vector<char>>& board, int i, int j) {
        if (!(i >= 0 && j >= 0 && i < board.size() && j < board[0].size()))
            return;
        if (board[i][j] == 'O')
            board[i][j] = 'Z';
        else return;
        dfs(board, i - 1, j);
        dfs(board, i + 1, j);
        dfs(board, i, j - 1);
        dfs(board, i, j + 1);
    }
    void solve(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[i].size(); j++)
                if ((i == 0 || j == 0 || i == board.size() - 1 || j == board[i].size() - 1) && (board[i][j] == 'O'))
                    dfs(board, i, j);

        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[i].size(); j++)
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == 'Z')
                    board[i][j] = 'O';
        return;
    }
};

作者：yu-yang-xian-yi
链接：https://leetcode-cn.com/problems/surrounded-regions/solution/c-bei-wei-rao-de-qu-yu-2020717-by-yu-yang-xian-yi/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

int main() {

    //Solution sl;
    Solution_DFS_v2 sl;
    //[["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
    std::vector<std::vector<char>> vt1 = 
    {{'X','X','X','X'}, 
     {'X','X','O','X'}, 
     {'X','X','O','X'}, 
     {'X','O','X','X'}};
    sl.solve(vt1);
    for(auto itt : vt1) {
        std::cout<<"[";
        for(auto it : itt) {
            std::cout<<"\""<<it<<"\",";
        }
        std::cout<<"],\n";
    }
    return 0;
}