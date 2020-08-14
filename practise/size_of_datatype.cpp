#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

int main() {

    std::cout<<"void* size : "<<sizeof(void*)<<"\n";//my 64-bit platform: 8 type
    std::cout<<"long size : "<<sizeof(long)<<"\n";//my platform : 4 byte
    std::cout<<"double size : "<<sizeof(double)<<"\n";//double 4 * 2 = 8 byte
    std::cout<<"float size : "<<sizeof(float)<<"\n";
    std::cout<<"long long size : "<<sizeof(long long)<<"\n";
    std::cout<<"int size : "<<sizeof(int)<<"\n";

    return 0;
}