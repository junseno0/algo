#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
Median is the middle value in an ordered integer list. If the size of the list is even,
there is no middle value. So the median is the mean of the two middle value.

For example,
[2,3,4], the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.

Follow up:

If all integer numbers from the stream are between 0 and 100, how would you optimize it?
If 99% of all integer numbers from the stream are between 0 and 100, how would you optimize it?
*/

/*
建立一个 小顶堆 A 和 大顶堆 B ，各保存列表的一半元素，两个堆保持平衡，小顶堆最多大于大顶堆一个元素，且规定：
A 保存 较大 的一半
B 保存 较小 的一半
易知，列表中间的两个数处于两个堆顶元素之间，中位数可仅根据 A, B 的堆顶元素计算得到。

addNum(num) 函数：
当小顶堆与大顶堆的大小相等时：需向 A 添加一个元素。实现方法：将新元素 num 插入至 B ，再将 B 堆顶元素插入至 A ；
当小顶堆大于大顶堆一个元素时：需向 B 添加一个元素。实现方法：将新元素 num 插入至 A ，再将 A 堆顶元素插入至 B ；

findMedian() 函数：
当小顶堆与大顶堆的大小相等时，元素总数为偶数，中位数为A, B堆顶元素之和的1/2。
否则，顶堆大于大顶堆一个元素，元素总数为奇数，中位数为小顶堆A的堆顶元素。
*/
class MedianFinder {
public:
    std::vector<int> maxheap;
    std::vector<int> minheap;
    /** initialize your data structure here. */
    MedianFinder() {
        //max heap
        maxheap.push_back(INT_MAX);
        //valid maxheap size = maxheap.size()-1
        //min heap
        minheap.push_back(INT_MIN);
        //valid minheap size = minheap.size()-1
    }
    void _maxshiftup(int num) {
        maxheap.push_back(num);
        int k = maxheap.size() - 1;
        while(k > 0) {
            //if parent val[k/2] smaller than val[k], swap
            //while k > 0
            if(maxheap[k/2] > maxheap[k]) break;
            std::swap(maxheap[k/2], maxheap[k]);
            k = k / 2;
        }
    }
    void _maxshiftdown() {
        int n = maxheap.size() - 1;
        maxheap[1] = maxheap[n];
        maxheap.erase(maxheap.end()-1);
        int k = 1;
        while( 2 * k <= n) {
            int j = 2 * k;
            if(j+1 <= n && maxheap[j+1] > maxheap[j]) {
                j++;
            }
            if(maxheap[k] > maxheap[j]) break;
            {
                std::swap(maxheap[k], maxheap[j]);
                k = j;
            }
        }
    }

    void _minshiftup(int num) {
        minheap.push_back(num);
        int k = minheap.size() - 1;
        while(k > 0) {
            if(minheap[k/2] < minheap[k]) break;
            std::swap(minheap[k/2], minheap[k]);
            k = k / 2;
        }
    }

    void _minshiftdown() {
        int n = minheap.size() -1;
        minheap[1] = minheap[n];
        minheap.erase(minheap.end()-1);
        int k = 1;
        while(2 * k <= n) {
             int j = 2 * k;
            if(j+1 <= n && minheap[j+1] < minheap[j]) {
                j++;
            }
            if(minheap[k] < minheap[j]) break;
            {
                std::swap(minheap[k], minheap[j]);
                k = j;
            }           
        }
    }

    int _delmax() {
        int val = maxheap[1];
        _maxshiftdown();
        return val;
    }
    int _delmin() {
        int val = minheap[1];
        _minshiftdown();
        return val;
    }
    
    void addNum(int num) {
        if(maxheap.size() == minheap.size()) {
            //add to min heap, before that, through max heap
            _maxshiftup(num);
            num = _delmax();
            _minshiftup(num);
        }
        else if(maxheap.size() < minheap.size()) {
            //add to max heap, before that, through min heap
            _minshiftup(num);
            num = _delmin();
            _maxshiftup(num);
        }
    }
    
    double findMedian() {
        //if max heap size = min heap size, average min and max
        if(maxheap.size() == minheap.size())
            return (double)( (double)maxheap[1] +  (double)minheap[1])/2;
        //if not, min val is median val
        else
            return (double)minheap[1];
    }
};

class MedianFinder_stl {
public:
    std::priority_queue<int> maxheap;
    std::priority_queue<int, vector<int>, greater<int>> minheap;
    /** initialize your data structure here. */
    MedianFinder_stl() {

    }
  
    void addNum(int num) {
        if(maxheap.size() == minheap.size()) {
            //add to min heap, before that, through max heap
            maxheap.push(num);
            num =maxheap.top();
            maxheap.pop();
            minheap.push(num);
        }
        else if(maxheap.size() < minheap.size()) {
            //add to max heap, before that, through min heap
            minheap.push(num);
            num = minheap.top();
            minheap.pop();
            maxheap.push(num);
        }
    }
    
    double findMedian() {
        //if max heap size = min heap size, average min and max
        if(maxheap.size() == minheap.size())
            return (double)( (double)maxheap.top() +  (double)minheap.top()) * 0.5;
        //if not, min val is median val
        else
            return (double)minheap.top();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main() {
    MedianFinder obj;
    //MedianFinder_stl obj;
    double val = 0.0;
    obj.addNum(1);
    obj.addNum(2);
    val = obj.findMedian();
    std::cout<<"obj find median : "<<val<<"\n";
    obj.addNum(3);
    val = obj.findMedian();
    std::cout<<"obj find median : "<<val<<"\n";
    return 0;
}