#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <queue>
/*
Please implement a function to find the first character that appears only once in the character stream.
For example, when the first two characters "go" are read only from the character stream,
the first character that appears only once is "g". When reading the first six characters "google" from the character stream,
the first character that appears only once is "l".

Difficulty: 1 star
Finished by self: yes
*/

class Solution_by_map
{
public:
  //Insert one char from stringstream
    std::queue<char> qchar;
    std::unordered_map<char, int> mp;
    void Insert(char ch)
    {
        if(mp[ch] == 0)
            qchar.push(ch);
         mp[ch]++;
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        while(!qchar.empty()) {
            if(mp[qchar.front()] == 1)
                return qchar.front();
            else
                qchar.pop();
        }
        return '#';
    }
};

/*
链接：https://www.nowcoder.com/questionTerminal/00de97733b8e4f97a3fb5c680ee10720?answerType=1&f=discussion

看到出现1次，第一想法肯定是使用基于Hash表的方法，如果不用库函数的话，那么就得使用数组，而使用一个数组的时候，就和Hash表一样，索引需要有独特的含义。
其实也就是需要自己实现一个和Hash类似功能的数组。当然可以有其他的一些变种的写法，但大致思想相同。

只使用一个数组，数组中不仅可以判断是否出现了多次，并且在出现一次时，数组中存放字符在字符流中出现第一次的位置，而数组索引和字符的ASCII码对应起来，由于ASCII码有128个字符，因此数组大小为128即可。
将数组初值赋值-1，某个字符第一次出现时，将-1更新成当前字符在字符流中的索引（位置）。
第二次出现时，将之前赋值的索引擦除，并且不用进入后续的判断，这里选择赋值成-2（赋值情况不唯一）。
也就是说，没出现过，数组记录-1，出现一次，数组记录位置，出现多次，数组记录成-2.
而在FirstAppearingOnce方法中，我们要遍历数组找到正确的解，所以我们要做两件事，第1是找到所有出现1次的字符，
由于要求我们返回第一次出现一次的字符，所以第2件事就是比较各个出现1次的字符在字符流中的位置，我们要找到最先出现的那个字符即位置最小的字符。
因此还需要设置一个变量，该变量记录某个字符的位置，在找到下一个出现一次的字符时，比较这两个只出现1次的字符的位置，看谁更靠前，就要谁。
（可以把这一过程理解成，在某个数组中找到最小的那个数，这个数就是第一个出现1次的字符的索引）
最妙的是，这个方法只利用一个数组，就完成了记录某个字符是否出现了一次，以及出现一次时的在字符流的位置。
*/
class Solution_by_smart_marking
{
public:
  //Insert one char from stringstream
    int pos;
    std::vector<int> vt;
    Solution_by_smart_marking(){
        pos = 0;
        for(int i = 0; i < 128; i++) vt.push_back(-1);
    };
    
    void Insert(char ch)
    {
        if(vt.at(ch) == -1) {
            vt.at(ch) =  pos++;
        } else if (vt.at(ch) >= 0){
            vt.at(ch) = -2;
        }
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        int val = INT_MAX;
        char ch = '#';
        for(int i = 0; i < 128; i++) {
            if(vt.at(i) > -1 && vt.at(i) < val) {
                val = vt.at(i);
                ch = (char)i;
            }
        }
        return ch;
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
    std::vector<char> vt = {'g', 'o', 'o', 'g', 'l', 'e'};

    Solution_by_map ss;
    for(auto it : vt) {
        ss.Insert(it);
        char ch = ss.FirstAppearingOnce();
        std::cout<<"Solution_by_map. FirstAppearingOnce : "<<ch<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n";

    Solution_by_smart_marking sk;
    for(auto it : vt) {
        sk.Insert(it);
        char ch = sk.FirstAppearingOnce();
        std::cout<<"Solution_by_smart_marking. FirstAppearingOnce : "<<ch<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n";

    return 0;
}
