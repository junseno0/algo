#include <iostream>
#include <cassert>
#include <ctime>
#include <algorithm>

using namespace std;
template<typename Item>
class MaxHeap{
    private:
    Item* data;
    int count;
    int capacity;
    public:
    MaxHeap(int capacity) : count(0), capacity(capacity){
        data = new Item[capacity+1];
        for(int i = 0; i <= capacity; i++) data[i] = 0;
        //this.capacity = capacity;
    }
    //Time complexity: O(n)
    MaxHeap(Item arr[], int n) {
        data = new Item[n+1];
        for(int i = 0; i < n; i++) {
            data[i+1] = arr[i];
        }
        count = n;
        capacity = n+1;
        for(int i = count/2; i > 0; i--) {
            _shiftdown(i);
        }
    }
    ~MaxHeap() {
        delete[] data;
    }
    int size()  {
        return count;
    }
    bool isEmpty() {
        return count == 0;
    }
    void _shiftup(int k) {
        while(k > 1 && data[k/2] < data[k]) {
            std::swap(data[k/2], data[k]);
            k = k/2;
        }
    }
    void insert(Item item) {
        assert(count+1 <= capacity);
        data[count + 1] = item;
        //k:parent 2*k : left node 2*k+1:right node
        //k: node  parent node: k / 2;
        count++;
        _shiftup(count);
    }
    void _shiftdown(int k) {
        int j = 0;
        while( 2 * k <= count/* || k * 2 + 1 <= count*/) {
            j = 2 * k;
            if( j + 1 <= count && data[j + 1] > data[j])
                j += 1;
            if(data[k] > data[j]) break;
            std::swap(data[k], data[j]);
            k = j;
        }
    }
    Item delMax() {
        Item val = data[1];
        //data[1] = data[count];
        std::swap(data[1], data[count]);
        count--;
        int k = 1;
        _shiftdown(k);
        return val;
    }
    void printheap() {
        for(int i = 1; i < capacity + 1; i++)
            std::cout<<"["<<data[i]<<"] ";
        std::cout<<"\n\n";
    }
};

void _shiftdown(int arr[], int sz, int k) {
    // node:k, last non-leaf node: (k-1) / 2
    std::swap(arr[0], arr[k]);
    while(2 * k + 1 < sz) {
        int j = 2 * k + 1;
        if(j + 1 < sz && arr[j+1] > arr[j]) {
            j += 1;
        }
        if(arr[k] > arr[j]) break;
        std::swap(arr[k], arr[j]);
        k = j;
    }
}
template<typename T>
void heapsort(int arr[], int n) {
    //heapify
    for(int i = (n-1-1) / 2; i >= 0; i--) {
        _shiftdown(arr, n, i);
    }
    //heap max to last and then shiftdown
    for(int i = n-1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        _shiftdown(arr, i, 0);
    }
}
int main() {
    MaxHeap<int> maxheap = MaxHeap<int>(18);
    srand(time(nullptr));
    for(int i = 0; i < 15; i++) {
        maxheap.insert(rand()%100);
    }
    std::cout<<"Before constructing MaxHeap randomly, arr :\n";
    maxheap.printheap();
    while(!maxheap.isEmpty()) {
        maxheap.delMax();
    }
    std::cout<<"After delMax MaxHeap, arr :\n";
    maxheap.printheap();

    int arr[5] = {2, 5, 7, 4, 10};
    std::cout<<"Before constructing MaxHeap with arr and n, arr :\n";
    for(int i = 0; i < 5; i++) std::cout<<"["<<arr[i]<<"] ";
    std::cout<<"\n\n";
    MaxHeap<int> mp2 = MaxHeap<int>(arr, 5);
    std::cout<<"After constructing MaxHeap with arr and n, printheap :\n";
    mp2.printheap();

    heapsort<int>(arr, 5);
    std::cout<<"After heap sort, arr :\n";
    for(int i = 0; i < 5; i++) std::cout<<"["<<arr[i]<<"] ";
    std::cout<<"\n\n";
    return 0;
}