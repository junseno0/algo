#include <iostream>
#include <list>
#include <algorithm>
#include <set>
#include <vector>

/*
在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。
也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。

Difficulty: 1~2 star
Finished by self: yes
*/

//Time complexity: O(n)
//Space complexity: O(n)
class Solution_by_set {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {
        std::set<int> st;
        for(int i = 0; i< length; i++) {
            if(st.count(numbers[i])) {
                *duplication = numbers[i];
                return true;
            }
            st.insert(numbers[i]);
        }
        return false;
    }
};

/*
* Refer to：https://www.nowcoder.com/questionTerminal/623a5ac0ea5b4e5f95552655361ae0a8?answerType=1&f=discussion
* 
* 设置一个指针i指向开头0，
* 
* 对于arr[i]进行判断，如果arr[i] == i， 说明下标为i的数据正确的放在了该位置上，让i++
* 
* 如果arr[i] != i, 说明没有正确放在位置上，那么我们就把arr[i]放在正确的位置上，也就是交换
* arr[i] 和arr[arr[i]]。交换之后，如果arr[i] ！= i, 继续交换。
* 
* 如果交换的过程中，arr[i] == arr[arr[i]]，说明遇到了重复值，返回即可。
*/
//Time complexity: O(n)
//Space complexity: O(n)
class Solution_by_traverse {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {
        std::vector<int> vt(length, 0);
        for(int i = 0; i < length; i++) {
            if(vt.at(numbers[i]) == 1) {
                *duplication = numbers[i];
                return true;
            }
            vt.at(numbers[i]) = 1;
        }
        return false;
    }
};

//Time complexity: O(n)
//Space complexity: O(1)
class Solution_by_in_place {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {
        int i = 0;
        while(i < length) {
            while(i != numbers[i]) {
                if (numbers[i] == numbers[numbers[i]]) {
                    *duplication = numbers[i];
                    return true;
                }
                std::swap(numbers[i], numbers[numbers[i]]);
            }
            i++;
        }
        return false;
    }
};

/*
* 在原数组上通过+length的方式达到开标记数组的目的
* 在开辟新的同样数组作标识的方法中，我们的思路是，对于“每个数的位置”进行标记，相当于这个数的位置被“占位”了
* 如果不开辟新的同样大小数组作标识，那我们怎么在原来的数组上作标识？
* 我们可以遍历数组，把每个数对应的位置的数字进行“特殊”标记，被标记过的数在下次访问的时候也要能够还原成原来的数
*/
//Time complexity: O(n)
//Space complexity: O(1)
class Solution_by_smart_mark {
public:
  bool duplicate(int numbers[], int length, int* duplication) {
      if (length <= 0 || numbers == NULL) {
          return false;
      }
      for (int i = 0; i < length; i++) {
          int index = numbers[i];
          if (index >= length) {
              index -= length;
          }
          if (numbers[index] >= length) {
              duplication[0] = index;
              return true;
          }
          numbers[index] += length;
      }
      return false;
  }
};

int main()
{
    int num[7] = {2,3,1,0,2,5,3};
    int duplication = -1;

    Solution_by_traverse st;
    st.duplicate(num, 7, &duplication);
    std::cout<<"Solution_by_traverse: duplicated val is "<<duplication<<"\n";

    Solution_by_set ss;
    ss.duplicate(num, 7, &duplication);
    std::cout<<"Solution_by_set: duplicated val is "<<duplication<<"\n";

    Solution_by_in_place sp;
    sp.duplicate(num, 7, &duplication);
    std::cout<<"Solution_by_in_place: duplicated val is "<<duplication<<"\n";

    Solution_by_smart_mark sm;
    sm.duplicate(num, 7, &duplication);
    std::cout<<"Solution_by_smart_mark: duplicated val is "<<duplication<<"\n";

    return 0;
}
