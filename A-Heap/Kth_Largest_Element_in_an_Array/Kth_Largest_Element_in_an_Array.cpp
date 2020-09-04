#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    void buildheap(std::vector<int>& nums, int sz, int k) {
        for(int i = (sz-1)/2; i >= 0; i--) {
            while(2 * i + 1 < sz) {
                int j = 2 * i + 1;
                if(j + 1 < sz && nums[j+1] > nums[j]) j++;
                if(nums[i] >= nums[j]) break;
                std::swap(nums[i], nums[j]);
                i = j;
            }
        }
    }
    int delMax(std::vector<int>& nums, int sz) {
            int val = nums[0];
            nums[0] = nums[sz-1];
            sz--;
            int i = 0;
            while(2 * i + 1 < sz) {
                int j = 2 * i + 1;
                if(j + 1 < sz && nums[j+1] > nums[j]) j++;
                if(nums[i] >= nums[j]) break;
                std::swap(nums[i], nums[j]);
                i = j;
            }
            return val;
    }
    int findKthLargest(std::vector<int>& nums, int k) {
        buildheap(nums, nums.size(), k);
        k--;
        int n = nums.size();
        while(k-- > 0) {
            //del max
            delMax(nums, n--);
        }
        return nums[0];
    }
};

class Solution_quickquicksort {
public:
    int partition(vector<int>& nums, int left, int right) {
        std::swap(nums[left], nums[rand() % (right - left + 1) + left]);//trick
        int pivot = nums[left];
        int j = left;
        //another partition trick
        for(int i = left+1; i <= right; i++) {
            if(nums[i] < pivot) {
                std::swap(nums[++j], nums[i]);
            }
        }
        std::swap(nums[left], nums[j]);
        return j;
    }
    /*
    int partition(vector<int>& nums, int left, int right) {
        std::swap(nums[left], nums[rand() % (right - left + 1) + left]);
        int pivot = nums[left];
        while(left < right) {
            while(left < right && nums[right] >= pivot) {
                right--;
            }
            //replace swap by assignment
            std::swap(nums[right], nums[left]);
            while(left < right && nums[left] < pivot) {
                left++;
            }
            //replace swap by assignment
            std::swap(nums[left], nums[right]);
        }
        nums[left] = pivot;
        return left;
    }
    */

    int findKthLargest(std::vector<int>& nums, int k) {
        //check
        if(nums.size() <= 0) return -1;
        //partition
        //if pivot pos == size - k, return pivot
        //if pivot pos > size - k, then partition left -- >pivotpos
        //otherwise partition pivotpos --> right
        int pivotpos = 0;
        int size = nums.size();
        int left = 0;
        int right = nums.size() - 1;
        while(left < right) {
            pivotpos = partition(nums, left, right);
            if(pivotpos == size - k) {
                return nums[pivotpos];
            } else if (pivotpos > size -k) {
                right = --pivotpos;//trick
            } else {
                left = ++pivotpos;//trick
            }
        }
        //return
        return nums[left];
    }
};

int main() {
    //Solution sl;
    Solution_quickquicksort sl;
    int val = 0;
    std::vector<int> vt1 = {2, 1};
    std::vector<int> vt2 = {5, -1, 5, 4, 3};
    std::vector<int> vt3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    val = sl.findKthLargest(vt1, 2);
    std::cout<<"sl find kth largetst: "<<val<<"\n";
    val = sl.findKthLargest(vt2, 3);
    std::cout<<"sl find kth largetst: "<<val<<"\n";
    val = sl.findKthLargest(vt3, 5);
    std::cout<<"sl find kth largetst: "<<val<<"\n";
    return 0;
}