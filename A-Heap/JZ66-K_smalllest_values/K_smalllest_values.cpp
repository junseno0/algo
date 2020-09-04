#include <iostream>
#include <list>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <vector>
using namespace std;

/*
JZ66 机器人的运动范围
*/

class Solution_DFS {
private:
    using V = vector<int>;
    using VV = vector<V>;
    int count;
    VV mark;
    VV dp = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int calculatenum(int n) {
        int num = 0;
        while(n) {
            num += n % 10;
            n /= 10;
        }
        return num;
    }
    void dfs(int threashold, int rows, int cols, int m , int n) {
        //if outside, return
        if(m < 0 || n < 0 || m >= rows || n >= cols || mark[m][n] == 1) return;
        //if mark, return
        //if(mark[m][n] == 1) return;
        //mark it
        //if satify, count it
        mark[m][n] = 1;
        if(calculatenum(m) + calculatenum(n) > threashold) return;
        count++;
        //dfs 4 dirctions
        for(int i = 0; i < 4; i++) {
            dfs(threashold, rows, cols, m+dp[i][0], n+dp[i][1]);
        }
    }
public:
    int movingCount(int threshold, int rows, int cols)
    {
        //check
        if(threshold < 0 || rows < 0 || cols < 0) return 0;
        //if any input para not satify ?? return what??
        count = 0;
        mark = VV(rows, V(cols, 0));
        dfs(threshold, rows, cols, 0, 0);
        return count;
    }
};

class Solution_BFS {
private:
    using V = vector<int>;
    using VV = vector<V>;
    int count;
    VV mark;
    VV dp = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int calculatenum(int n) {
        int num = 0;
        while(n) {
            num += n % 10;
            n /= 10;
        }
        return num;
    }
    void _movingCount(int threashold, int rows, int cols, std::queue<std::vector<int>> &qt) {
        //bfs -- queue
        //while n count in st, pop each one, and push its around ones input st
        //check each one if satisfy
        while(!qt.empty()) {
            std::vector<int> vt = qt.front();
            qt.pop();
            count++;
            for(int i = 0; i < 4; i++) {
                int m = vt[0] + dp[i][0];
                int n = vt[1] + dp[i][1];
                if(m < 0 || n < 0 || m >= rows || n >= cols || mark[m][n] == 1) continue;
                mark[m][n] = 1;
                if(calculatenum(m) + calculatenum(n) <= threashold) 
                    qt.push({m, n});
            }
        }
    }
public:
    int movingCount(int threshold, int rows, int cols)
    {
        //check
        if(threshold <= 0 || rows <= 0 || cols <= 0) return 0;
        //if any input para not satify ?? return what??
        count = 0;
        mark = VV(rows, V(cols, 0));
        std::queue<std::vector<int>> qt;
        qt.push({0,0});
        mark[0][0] = 1;
        _movingCount(threshold, rows, cols, qt);
        return count;
    }
};

int main()
{
    Solution_DFS sl;
    int res = sl.movingCount(10, 10, 10);
    std::cout<<"moving count with 10, 10, 10 :"<<res<<"\n";
    Solution_BFS sb;
    res = sb.movingCount(10, 10, 10);
    std::cout<<"moving count with 10, 10, 10 :"<<res<<"\n";
    return 0;
}
