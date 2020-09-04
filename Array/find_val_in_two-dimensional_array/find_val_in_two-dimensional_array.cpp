#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>

/*
在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

Difficulty: 2~3 star
Finished by self: not
*/

/*
* 暴力解法。
* Attentions:
* 1.
* C++ STL库函数： template <class ForwardIterator, class T>
* bool binary_search (ForwardIterator first, ForwardIterator last, const T& val);
* Returns true if any element in the range [first,last) is equivalent to val, and false otherwise.
* 2.
* set iterator for two-dimension vector, even three-dimension vector.
* 3.
* template <class ForwardIterator, class T>
* ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val);
* Returns an iterator pointing to the first element in the range [first,last) which does not compare less than val.
* 4.
* template <class ForwardIterator, class T>
* ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val);
* Returns an iterator pointing to the first element in the range [first,last) which compares greater than val.                 
*/
// Time complexity: O(mlogn). Space complexity: O(1)
class Solution_by_traversal_binary_search {
public:
    bool Find(int target, std::vector<std::vector<int>> array) {
        //check
        if(array.empty() || array.at(0).empty()) return false;
        //for each row, search target with binary search method.
        std::vector<std::vector<int>>::iterator row;
        std::vector<int>::iterator col;
        for(row = array.begin(); row != array.end(); row++) {
            std::vector<int>::iterator first = (*row).begin();
            std::vector<int>::iterator last = (*row).end();
            for(col = (*row).begin(); col != (*row).end(); col++) {
                if(std::binary_search(first, last, target) == true) return true;
            }
        }
        return false;
    }
};

/*
* Similar with Solution_by_traversal_binary_search
* Binary search function is coded manually.
*/
// Time complexity: O(mlogn). Space complexity: O(1)
class Solution_by_traversal_binary_search_v2 {
public:
    bool binarySearch(std::vector<int> array, int size, int target) {
        //check
        //[left, right]
        int left = 0;
        int right = size - 1;
        int mid = 0;
        while(left <= right) { // attention : <= , trick here, since mid+1 or mid-1
            if(array.at(left) > target || array.at(right) < target) break;
            if(array.at(left) == target || array.at(right) == target) return true;
            //!!! It's NOT okay to set mid = left + (right - left) >> 1
            mid = (left + right) / 2;
            if (array.at(mid) == target) return true;
            else if (array.at(mid) < target) left = mid + 1;
            else if (array.at(mid) > target) right = mid - 1;
        }
        return false;
    }
    bool Find(int target, std::vector<std::vector<int> > array) {
        //check
        if(array.empty() || array.at(0).empty()) return false;
        //for each row, search target with binary search method.
        int row = array.size();
        int col = array.at(0).size();
        for(int i = 0; i < row; i++) {
            if(binarySearch(array.at(i), col, target)) return true;
        }
        return false;
    }
};

/*
* 二分查找
* 直接按照一维数组的二分法，则二分之后，无法确定下一次二分应该往哪边分，由此无法进行二分下去。
* 如果我们找个位置，每次都能确定的往哪个部分二分，即可达到我们想要的结果。
* 二分不一定是对半分。
* 如果我们把二分值定在右上角或者左下角，就可以进行二分。
 */
// Time complexity: O(m+n). Space complexity: O(1)
class Solution_by_matrix_binary_search {
public:
    bool Find(int target, std::vector<std::vector<int>> array) {
        //check
        if(array.empty() || array.at(0).empty()) return false;
        int row = array.size();
        int col = array.at(0).size();
        int i = 0;
        int j = col - 1;
        while(i < row && j >= 0) {
            if(array.at(i).at(j) == target) {
                return true;
            } else if(array.at(i).at(j) > target) {
                j--;
            } else if(array.at(i).at(j) < target) {
                i++;
            } else {
                return false;
            }
        }
        return false;
    }
};

int main()
{
    int target = 4;
    std::vector<std::vector<int>> row;
    std::vector<int> col1, col2;
    col1.push_back(1);
    col1.push_back(4);
    col1.push_back(6);
    col2.push_back(2);
    col2.push_back(6);
    col2.push_back(6);
    row.push_back(col1);
    row.push_back(col2);

    Solution_by_traversal_binary_search *sl = new Solution_by_traversal_binary_search();
    bool found = sl->Find(target, row);

    Solution_by_traversal_binary_search_v2 *sv = new Solution_by_traversal_binary_search_v2();
    found = sv->Find(target, row);

    Solution_by_matrix_binary_search *st = new Solution_by_matrix_binary_search();
    found = st->Find(target, row);
    (void) found;

    delete sl;
    delete sv;
    delete st;
    return 0;
}
