#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>

/*
Enter a matrix and print out each number in clockwise order from the outside to the inside.
For example, if you enter the following 4 X 4 matrix: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
then print out in turn Numbers 1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10.
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下4 X 4矩阵：
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.

Difficulty: 1 star
Finished by self: yes
*/

class Solution {
public:
    void printmaxtrix(std::vector<std::vector<int>> matrix, std::vector<int> &vt,
                    int startrow, int endrow,
                    int startcol, int endcol) {
        //startrow, startcol --> endcol
        //startrow+1 --> endrow, endcol
        //endrow, endcol-1 --> startcol
        //endrow-1 -->  startrow+1, startcol 
        for(int i = startcol; i <= endcol; i++) vt.push_back(matrix[startrow][i]);
        for(int j = startrow+1; j <= endrow; j++) vt.push_back(matrix[j][endcol]);
        if(startrow < endrow)
            for(int i = endcol-1; i >= startcol; i--) vt.push_back(matrix[endrow][i]);
        if(startcol < endcol)
            for(int j = endrow-1; j >= startrow+1; j--) vt.push_back(matrix[j][startcol]);
    }
    std::vector<int> printMatrix(std::vector<std::vector<int> > matrix) {
        std::vector<int> vt;
        int rowsize =matrix.size();
        
        int colsize = 0;
        if(rowsize > 0) colsize = matrix[0].size();
        if(rowsize == 0 || colsize == 0) return vt;
        int startrow = 0;
        int startcol = 0;
        int endrow = rowsize - 1;
        int endcol = colsize - 1;
        while((startrow <= endrow) && (startcol <= endcol)) {
            printmaxtrix(matrix, vt, startrow++, endrow--, startcol++, endcol--);
        }
        return vt;
    }
};

void traversevector(std::vector<int> &vt)
{
    unsigned int i = 0;
    std::cout<<"vector list: [";
    for(i = 0; i < vt.size(); i++) {
        std::cout<<vt.at(i)<<" ";
    }
    std::cout<<"]\n";
}

int main()
{
    std::vector<int> vt1 = {1, 2, 3, 4};
    std::vector<int> vt2 = {5, 6, 7, 8};
    std::vector<int> vt3 = {9, 10, 11, 12};
    std::vector<int> vt4 = {13, 14, 15, 16};
    std::vector<std::vector<int>> vt = {vt1, vt2, vt3, vt4};
    Solution sl;
    std::vector<int> ret = sl.printMatrix(vt);
    traversevector(ret);
    std::cout<<"\n";

    return 0;
}
