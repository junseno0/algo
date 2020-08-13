#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;

/*https://www.cnblogs.com/nanqiang/p/9937175.html*/
/*适用C函数strlen的时候需要注意字符串参数是否为空，对空指针调用strlen会引发内存错误。*/
class c2string  {
private:
    char* data;
public:
    c2string() {
        data = new char[1];
        *data = '\0';
    }
    c2string(const char* chr) {
        if(chr == nullptr) {
            data = new char[1];
            *data = '\0';
        }
        else {
            int len = strlen(chr);
            data = new char[len+1];
            strcpy(data, chr);
        }
    }
    c2string(const c2string& rhs){
        int len = strlen(rhs.data);
        data = new char[len+1];
        strcpy(data, rhs.data);

    }
    c2string& operator=(const c2string& rhs) {
        if(&rhs == this) return *this;//检查自赋值
        delete data;//释放原有的内存资源
        int len = strlen(rhs.data);
        data = new char[len+1];
        strcpy(data, rhs.data);
        return *this;//返回本对象的引用
    }
    const char operator[](int n) {
        if(n >= strlen(data)) return data[strlen(data)-1];
        return data[n];
    }
    const char* c_str() const{
        return this->data;
    }
    size_t size() const{
        return strlen(data);
    }
    friend istream& operator>>(istream &is, c2string &str);//输入
    friend ostream& operator<<(ostream &os, c2string &str);//输出
    ~c2string() {
        delete[] data;
    }
};
istream& operator>>(istream &is, c2string &str) {
    char rhs[1023];
    is >> rhs;
    str.data = new char(strlen(rhs)+1);
    strcpy(str.data, rhs);
    return is;
}
ostream &operator<< (ostream &os, c2string &str) {
    os<<str.data;
    return os;
}
int main() {
    c2string* str_null = new c2string();
    std::cout<<"null str: "<<*str_null<<"\n\n";
    delete str_null;
    c2string* str_s = new c2string("simplecomponent");
    std::cout<<*str_s<<"\n\n";
    delete str_s;
    c2string str_avc = "avccomponent.";
    std::cout<<str_avc<<"\n\n";
    c2string str_aac("aaccomponent.");
    std::cout<<str_aac<<"\n\n";
    std::cout<<"first char of str_aac: "<<str_aac[0]<<"\n\n";
    return 0;
}