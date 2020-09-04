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
LL今天心情特别好,因为他去买了一副扑克牌,发现里面居然有2个大王,2个小王(一副牌原本是54张^_^)...
他随机从中抽出了5张牌,想测测自己的手气,看看能不能抽到顺子,如果抽到的话,他决定去买体育彩票,嘿嘿！！
“红心A,黑桃3,小王,大王,方片5”,“Oh My God!”不是顺子.....LL不高兴了,他想了想,决定大\小 王可以看成任何数字,
并且A看作1,J为11,Q为12,K为13。上面的5张牌就可以变成“1,2,3,4,5”(大小王分别看作2和4),“So Lucky!”。
LL决定去买体育彩票啦。 现在,要求你使用这幅牌模拟上面的过程,然后告诉我们LL的运气如何，
如果牌能组成顺子就输出true，否则就输出false。为了方便起见,你可以认为大小王是0。

LL was in a very good mood today, because he went to buy a deck of playing cards and found
that there were 2 big kings and 2 little kings in it (a deck of cards was originally 54 ^_^)...
he randomly drawn 5 cards from it. I want to test my luck and see if he can draw a straight.
If he draws, he decides to buy a sports lottery, hehe! ! "Heart Ace, 3 of Spades, Little King, Big King,
Square Piece 5", "Oh My God!" is not a straight... LL is not happy, he thought about it, and decided that
Big \ Little King can be regarded as Any number, and A is regarded as 1, J is 11, Q is 12, and K is 13.
The 5 cards above can be turned into "1,2,3,4,5" (big and small kings are regarded as 2 and 4 respectively),
"So Lucky!". LL decided to buy a sports lottery. Now, you are asked to use this card to simulate the above process,
and then tell us how lucky LL is. If the card can form a straight, it will output true,
otherwise it will output false. For convenience, you can consider the size king to be 0.

Difficulty: 1 star
Finished by self: yes
*/

class Solution_by_judge {
public:
    bool IsContinuous(std::vector<int> numbers ) {
        if(numbers.size() == 0) return false;
        std::vector<int> vt;
        for(auto it : numbers) {
            if(it != 0) {
                vt.push_back(it);
            }
        }
        if(vt.size() == 1) return true;
        for(int i = 1; i < vt.size(); i++) {
            if(vt.at(i) == vt.at(i-1)) return false;
        }
        std::sort(vt.begin(), vt.end());
        if((vt.back() - vt.front())< 5) return true;
        return false;
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
    std::vector<int> vt1 = {1, 2, 0, 0, 5};
    std::vector<int> vt2 = {1, 2, 0, 0, 6};
    std::vector<int> vt3 = {1, 9, 0, 0, 0};
    std::vector<std::vector<int>> vt = {vt1, vt2, vt3};
    Solution_by_judge ss;
    for(auto it : vt) {
        bool flag = ss.IsContinuous(it);
        std::cout<<"Solution_by_judge. IsContinuous : "<<flag<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n";

    return 0;
}
