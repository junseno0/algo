#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <string>

using namespace std;

/*
51. N-Queens

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
* 这解法存在太多可优化的地方，包括可放置位置的可行性判断，字符串的生成，历史位置的存放数据结构。
* 容易出错的地方是，在哪里回溯退栈。
*/
class Solution_v1 {
private:
    std::vector<std::vector<string>> ret;    
    bool available(std::vector<std::pair<int, int>> pos, int row, int col) {
        //check current chess if conflict with anyone in pos matrix.
        //pick chess from pos matrix
        //check if picked chess and current chess x same ? y same ?  on same diagonal line?
        for(int i = 0; i < pos.size(); i++) {
            std::pair<int, int> rc = pos[i];
            if( rc.first == row || rc.second == col ||
                (rc.first - row == rc.second - col) ||
                (rc.first - row == col - rc.second) )
                return false;
        }
        return true;
    }
    std::string placementOfQ(int n, int pos) {
        std::string str(n, '.');
        str[pos] = 'Q';
        return str;
    }
    //row indicates the row number to place a Queen
    void dfs(int n, std::vector<std::pair<int, int>> pos, std::vector<string> path, int row) {
        //terminate case
        std::cout<<"dfs row: "<<row<<"\n";
        for(auto it : pos) {
            std::cout<<"["<<it.first<<", "<<it.second<<"]\n";
        }
        if(row == n) {
            ret.push_back(path);
            std::cout<<"wonderful!!! ret push back one path\n";
            for(auto it : path) std::cout<<"["<<it<<"] ";
            std::cout<<"\n";
            return;
        }
        //backtracking
        for(int col = 0; col < n; col++) {
            //place a Queen in row index col i, okay?
            if(available(pos, row, col) == true) {
                std::cout<<"placement of ["<<row<<", "<<col<<"] is okay.\n";
                path.push_back(placementOfQ(n, col));
                pos.push_back(make_pair(row, col));
                dfs(n, pos, path, row+1);
                path.pop_back();//trick
                pos.pop_back();//trick
            }
            std::cout<<"next col to place a chess.\n";
        }
        std::cout<<"no position is okay to place a chess. return.\n";
        return;
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        //check
        if(n <= 0) return ret;
        std::vector<string> path;
        path.clear();
        std::vector<std::pair<int, int>> pos;
        dfs(n, pos, path, 0);
        return ret;
    }
};

/*
* 1, 采用引用
* 2，采用合适的方式生成chessboard，在最后的时候根据向量生成一个可行的棋谱方案
* 3，采用mark的方式判断是否皇后冲突
*/
class Solution_v2 {
private:
    std::vector<std::vector<string>> ret;
    std::vector<int> col;
    std::vector<int> hill;
    std::vector<int> dale;
    bool available(int n, int row, int col, 
        std::vector<int> &colmark, std::vector<int> &hillmark, std::vector<int> &dalemark) {
        //check current chess if conflict with anyone in pos matrix.
        //pick chess from pos matrix
        //check if picked chess and current chess x same ? y same ?  on same diagonal line?
        if(colmark[col] == 1 || hillmark[row+col] == 1 || dalemark[row-col+n-1] == 1) return false;
        return true;
    }
    std::vector<string> generateboard(int n, std::vector<int> path) {
        std::vector<string> res;
        res.clear();
        for(int i = 0; i < path.size(); i++) {
            std::string str(n, '.');
            str[path[i]] = 'Q';
            res.push_back(str);
        }
        
        return res;
    }
    //row indicates the row number to place a Queen
    void dfs(int n,  std::vector<int> &path, int row,
                std::vector<int> &colmark, std::vector<int> &hillmark, std::vector<int> &dalemark) {
        //terminate case
        //std::cout<<"dfs row: "<<row<<"\n";
        //for(auto it : pos) {
            //std::cout<<"["<<it.first<<", "<<it.second<<"]\n";
        //}
        if(row == n) {
            ret.push_back(generateboard(n, path));
            //std::cout<<"wonderful!!! ret push back one path\n";
            //for(auto it : path) std::cout<<"["<<it<<"] ";
            //std::cout<<"\n";
            return;
        }
        //backtracking
        for(int col = 0; col < n; col++) {
            //place a Queen in row index col i, okay?
            if(available(n, row, col, colmark, hillmark, dalemark) == true) {
                //std::cout<<"placement of ["<<row<<", "<<col<<"] is okay.\n";
                path.push_back(col);
                colmark[col] = 1;
                hillmark[row+col] = 1;
                dalemark[row-col+n-1] = 1;

                dfs(n, path, row+1, colmark, hillmark, dalemark);

                path.pop_back();
                colmark[col] = 0;
                hillmark[row+col] = 0;
                dalemark[row-col+n-1] = 0;
            }
            //std::cout<<"next col to place a chess.\n";
        }
        //std::cout<<"no position is okay to place a chess. return.\n";
        return;
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        //check
        if(n <= 0) return ret;
        std::vector<int> path;
        path.clear();
        col = std::vector<int>(n, 0);
        hill = std::vector<int>(2*n+1, 0);
        dale = std::vector<int>(2*n+1, 0);
        dfs(n, path, 0, col, hill, dale);
        return ret;
    }
};

/*
//这种处理生成棋谱方案的方式更为巧妙！
//默认board都是“.”，在可行的位置上修改为“Q”，回溯的时候重新修改为“.”。

for(int col=0; col<n; ++col){
    if(!isValid(board, row, col)){
        continue;
    }

    board[row][col] = 'Q';
    backtrack(board, row+1, res);
    board[row][col] = '.';
}

作者：happyfire
链接：https://leetcode-cn.com/problems/n-queens/solution/hui-su-suan-fa-jing-dian-li-ti-nhuang-hou-cxiang-j/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int main() {

    Solution_v2 sl;
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