#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
37. Sudoku Solver

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
Empty cells are indicated by the character '.'.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sudoku-solver
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
#include <stdlib.h>
#include <stdio.h>

/*
* 犯错的地方有：1，未考虑递归终止条件是全部解还是一个解，2，未采用合适的方式标记是否存在重复
* 大家的思路都是整体明确的，套路也是知道的，但是否成功取决于细节的理解与合适解决方案
*/
class Solution_v1 {
private:
    inline bool valid(vector<vector<char>>& board, int x, int y, int val) {
        //check same row
        //check same col
        //check same 3x3 place
        int r = x;
        int c = y;
        for (int i = 0; i < 9; i++) {
            // 判断行是否存在重复
            if (board[r][i] ==  char(val+'0')) return false;
            // 判断列是否存在重复
            if (board[i][c] ==  char(val+'0')) return false;
            // 判断 3 x 3 方框是否存在重复
            if (board[(r/3)*3 + i/3][(c/3)*3 + i%3] ==  char(val+'0'))
                return false;
        }
        return true;
    }

    inline void putOneVal(vector<vector<char>>& board,int x, int y, int val) {
        board[x][y] = char(val+'0');
    }

    inline void removeOneVal(vector<vector<char>>& board, int x, int y) {
        board[x][y] = '.';
    }

    bool dfs(vector<vector<char>>& board, int x, int y) {
        //check if x, y in area and empty
        if(x == 9) return true;
        if(y == 9) {
            x = x+1;
            y = 0;
            return dfs(board, x, y);
        }
        if(board[x][y] != '.') 
            return dfs(board, x, y+1);
        //backtracking
        //select one val, check if valid, if yes, put in current empty position
        //if no, backtrack
        for(int val = 1; val <= 9; val++) {
            if(valid(board, x, y, val)) {
                putOneVal(board, x, y, val);
                 // 如果找到一个可行解，立即结束 trick here
                if(dfs(board, x, y+1))
                    return true;    //trick !!!!
                
                removeOneVal(board, x, y);
            }
        }
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        //check
        if(board.size() <= 0) return;
        //backtracking
        dfs(board, 0, 0);
        //return
        return;
    }
};

/*
* 1，将坐标转换成第几个宫格
* 2，采用map方式标记
* 这些都大大节省了时间内存，非常棒的写法，学习了。
* https://leetcode-cn.com/problems/sudoku-solver/solution/hui-su-fa-jie-shu-du-by-i_use_python/
*/
/*
class Solution {
    public void solveSudoku(char[][] board) {
        if (board == null || board.length != 9 || board[0].length != 9) return;
        boolean[][] row = new boolean[9][9], col = new boolean[9][9], box = new boolean[9][9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                int num = board[i][j] - '1', k = (i / 3) * 3 + j / 3;
                row[i][num] = col[j][num] = box[k][num] = true;
            }
        }
        solveSudokuHelper(board, 0, row, col, box);
    }

    boolean solveSudokuHelper(char[][] board, int n, boolean[][] row, boolean[][] col, boolean[][] box) {
        if (n == 81) return true;
        int i = n / 9, j = n % 9;
        if (board[i][j] != '.') return solveSudokuHelper(board, n + 1, row, col, box);

        int k = (i / 3) * 3 + j / 3;
        for (int num = 0; num < 9; num++) {
            if (row[i][num] || col[j][num] || box[k][num]) continue;
            board[i][j] = (char) (num + '1');
            row[i][num] = col[j][num] = box[k][num] = true;
            if (solveSudokuHelper(board, n + 1, row, col, box)) return true;
            row[i][num] = col[j][num] = box[k][num] = false;
        }
        board[i][j] = '.';
        return false;
    }
}
*/

int main() {

    Solution_v1 sl;
    std::vector<std::vector<string>> res;
    int n = 4;
    res = sl.solveNQueens(4);
    for(int i = 0; i < res.size(); i++) {
        for(int j = 0; j < n; j++) 
            std::cout<<res[i][j]<<"\n";
        std::cout<<"\n";
    }
    return 0;
}