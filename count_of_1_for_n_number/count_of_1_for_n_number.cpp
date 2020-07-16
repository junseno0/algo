#include <iostream>
#include <list>
#include <algorithm>
#include <map>

/*
求出1~13的整数中1出现的次数,并算出100~1300的整数中1出现的次数？
为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,但是对于后面问题他就没辙了。
ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数（从1 到 n 中1出现的次数）。

Difficulty: 2~3 star
Finished by self: not
*/

/*
* 暴力解法，必须得学会。
*/
class Solution_by_traverse {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int count=0;
        for(int i=n;i>0;i--){
            for(int j=i;j>0;j/=10){
                if(j%10==1) count++;
            }
        }
    return count;    
    }
};

/*
* 将一个数字中1出现的次数拆成个、十、百位中1出现次数的和
* 假设数字为321
* 个位为1的数字有多少个？将321拆为高位32，低位1，固定个位为1，高位变化范围可以从0~31，不管真实个位是多少，该数字均存在，数字个数为count[0~31]，即32个
* 当高位为32时，真实个位数值为1，320~329的范围内存在321，因此高位还可以取32，存在1个数字满足固定个位为1的条件
* 因此，个位为1的数字有 32 + 1 = 33 个
* 十位为1的数字有多少个？将321拆为高位3，低位21，固定十位为1，高位变化范围可以从0~2，不管真实低位是多少，该数字均存在，数字个数为count[0~2] * 10，即 3*10 个
* 当高位为3时，真实低位数值为21，300~399的范围内存在310~319，因此高位可以取3，存在10个数字满足固定十位为1的条件
* 因此，十位为1的数字有 30 + 10 = 40 个
* 百位为1的数字有多少个？将321拆为高位0，低位321，固定百位为1，高位变化范围不存在
* 真实低位为321，100~999的范围内存在100~199，因此存在100个数字满足固定百位为1的条件
* 因此，百位为1的数字有 0 + 100 = 100 个
* 假设数字可能为321， 315， 305
* 当高位为3时，高位的变化范围是相同的，相应的个数也是相同的，如何确定低位下固定低位首位为1的条件下有多少个数字？
* 对于321，低位为21，满足低位首位为1的条件的数字有10个，对于315，则为5+1=6个，对于305，则为0个
* 发现，低位首位 > 1, 则满足低位首位为1的条件的数字有10个，低位首位为1，则为15-10+1=6个，低位首位为0，则为0个
* 当高位32，低位为1时，同样的道理，低位首位 > 1, 则满足低位首位为1的条件的数字有1个，低位首位为1，则为1-1+1=1个，低位首位为0，则为0个
* 再缕一下，高位为3，低位21，大于等于低位首位为1的条件的数字有21 - 10 + 1一共12个，=满足低位首位为1的条件的数字最多取10个
* 高位为3，低位为15，大于等于低位首位为1的条件的数字有15 - 10 + 1一共6个，满足低位首位为1的条件的数字最多取6个
* 高位为3，低位为05，大于等于低位首位为1的条件的数字有5 - 10 + 1一共负4个，满足低位首位为1的条件的数字最少取0个
* 也就是说，假设低位为n(i)n(i-1)...n(1), times = 10^(i-1), 计算n(i)n(i-1)...n(1) - times + 1为满足条件数字的个数，但最少取0个，最多取times个
* 因此，低位下固定低位首位为1的条件下的数字有std::min(std::max(n % (times * 10) - times + 1, 0), times)个
*/
class Solution_by_high_low {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int count = 0;
        int times = 1;
        while(times <= n) {
            count += ( n / (times * 10) ) * times + std::min(std::max(n % (times * 10) - times + 1, 0), times);
            times *= 10;
        }
        return count;
    }
};

/*
* https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/solution/mian-shi-ti-43-1n-zheng-shu-zhong-1-chu-xian-de-2/
* 将 1 ~ n 的个位、十位、百位、...的 1 出现次数相加，即为 1 出现的总次数。
* 设置当前位，高位，低位与位因子。
* 根据当前位cur的取值不同，某位出现1的次数的计算方法亦不同。
* 分为三种情况，cur = 0, 由高位决定，cur = 1, 由高位与低位共同决定，cur > 1,由高位决定，多加一个位因子的数量
*/
/*
class Solution:
    def countDigitOne(self, n: int) -> int:
        digit, res = 1, 0
        high, cur, low = n // 10, n % 10, 0
        while high != 0 or cur != 0:
            if cur == 0: res += high * digit
            elif cur == 1: res += high * digit + low + 1
            else: res += (high + 1) * digit
            low += cur * digit
            cur = high % 10
            high //= 10
            digit *= 10
        return res
*/

class Solution_by_Krahets_idea {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int count = 0;
        int bitfactor = 1;
        int high, cur, low;
        while(bitfactor <= n) {
            high = n / (bitfactor * 10);
            cur = n % (bitfactor * 10) / bitfactor;
            low = n % (bitfactor * 10) % bitfactor;
            if(cur == 0) {
                count += high * bitfactor;
            } else if (cur == 1) {
                count += high * bitfactor + low + 1;
            } else if (cur > 1) {
                count += (high + 1) * bitfactor;
            }
            bitfactor *= 10;
        }
        return count;
    }
};

int main()
{
    //test cases: 0, 1, 9, 10, 19, 21, 100, 321
    Solution_by_high_low *sl = new Solution_by_high_low();
    int n = sl->NumberOf1Between1AndN_Solution(321);
    std::cout<<"count solved by deviding high and low bits: "<<n<<"\n";
    
    Solution_by_Krahets_idea *st = new Solution_by_Krahets_idea();
    n = st->NumberOf1Between1AndN_Solution(321);
    std::cout<<"count solved by Krahets_idea: "<<n<<"\n";

    delete sl;
    delete st;
    return 0;
}
