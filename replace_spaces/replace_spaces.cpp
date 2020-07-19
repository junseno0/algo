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
请实现一个函数，将一个字符串中的每个空格替换成“%20”。
例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

Please implement a function to replace every space in a string with "%20".
For example, when the string is We Are Happy. The replaced string is We%20Are%20Happy.

Difficulty: 1 star
Finished by self: yes
*/

class Solution_by_reconstruction {
public:
	void replaceSpace(char *str,int length) {
        //check
        if(!str) return;
        //check count of space
        int space_count = 0;
        for(int i = 0; i < length; i++) {
            if(*(str+i) == ' ') space_count++;
        }
        //extend count * 2 length
        //backstep for each substr
        int offset = 2 * space_count;
        // NOTICE, maybe str[length] need to be copied.
        for(int i = length - 1; i >= 0; i--) {
            if(*(str+i) != ' ') {
                *(str+i+offset) = *(str+i);
            } else {
                offset -= 2;
                *(str+i+offset) = '%';
                *(str+i+offset+1) = '2';
                *(str+i+offset+2) = '0';
            }
        }
        //return
        return;
	}
};

// ugly *(str+i) style for char
/*
class Solution {
public:
	void replaceSpace(char *str,int length) {
        //check
        if(!str) return;
        //check count of space
        char *p = str;
        int space_count = 0;
        for(int i = 0; i < length; i++) {
            if(*(str+i) == ' ') space_count++;
        }
        
        //extend count * 2 length
        int newlength = length + 2 * space_count - 1;
         // NOTICE, maybe str[length] need to be copied.
        for(int i = length - 1; i >= 0; i--) {
            if(*(str+i) != ' ') {
                *(str+newlength) = *(str+i);
                newlength--;
            } else {
                *(str+newlength) = '0';
                newlength--;
                *(str+newlength) = '2';
                newlength--;
                *(str+newlength) = '%';
                newlength--;
            }
        }
        //backstep for each substr
        
        //return
        return;
	}
};
*/

// nice str[i] style for char
/*
class Solution {
public:
	void replaceSpace(char *str,int length) {
        //check
        if(!str) return;
        //check count of space
        char *p = str;
        int space_count = 0;
        for(int i = 0; i < length; i++) {
            if(str[i] == ' ') space_count++;
        }
        
        //extend count * 2 length
        int newlength = length + 2 * space_count;
         // NOTICE, maybe str[length] need to be copied.
        for(int i = length - 1; i >= 0; i--) {
            if(str[i] != ' ') {
                str[--newlength] = str[i];
            } else {
                str[--newlength] = '0';
                str[--newlength] = '2';
                str[--newlength] = '%';
            }
        }
        //backstep for each substr
        //return
        return;
	}
};
*/

/*
//链接：https://www.nowcoder.com/questionTerminal/4060ac7e3e404ad1a894ef3e17650423?answerType=1&f=discussion
// Refer to similar memmove function implememtation.
void* __cdecl memmove (void *dst, const void *src, size_t count) 
{
    void *ret = dst;
    if (dst <= src || (char *)dst >= ((char *)src + count)) 
    {
        // 若dst 和 src区域没有重叠，则从起始处开始逐一拷贝
        while (count--) 
        {
            *(char *)dst = *(char *)src;
            dst = (char *)dst + 1;
            src = (char *)src + 1;
        }
    }
    else 
    {
        // 区域重叠，从尾部开始拷贝
        dst = (char *)dst + count - 1;
        src = (char *)src + count - 1;
        while (count--) 
        {
            *(char *)dst = *(char *)src;
            dst = (char *)dst - 1;
            src = (char *)src - 1;
        }
    }
    return (ret);
}
*/

#include <string.h>
class Solution_by_copy_string {
public:
 void replaceSpace(char *str,int length) {
     if (str == nullptr || length <= 0) return;
     std::string st = "";
     for(int i = 0; i < length; i++) {
         if (str[i] != ' ') {
             st += str[i];
         } else {
             st += "%20";
         }
     }
     //string to char
     strcpy(str, st.c_str());
     return;
 }
};

int main()
{
    char log[14] = "we are happy!";
    Solution_by_copy_string ss;
    ss.replaceSpace(log, 14);
    std::cout<<"Solution_by_copy_string. replaceSpace : "<<log<<"\n";

    char log2[14] = "we are happy!";
    Solution_by_reconstruction sr;
    sr.replaceSpace(log2, 14);
    std::cout<<"Solution_by_reconstruction. replaceSpace : "<<log2<<"\n";

    return 0;
}
