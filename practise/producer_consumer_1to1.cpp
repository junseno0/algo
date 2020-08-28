#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <unistd.h>
#include <string.h>

using namespace std;

std::mutex mtx;
std::condition_variable cv;
bool ready = false;
std::deque<int> dq;

void producer() {
    while(true) {
        int data = rand() % 1000;
		{
        	std::unique_lock<std::mutex> lck(mtx);
        	dq.push_back(data);
			cout<<"deque push :"<<data<<endl;
        	cv.notify_all();
		}
        sleep(1);
    }
} 

void consumer() {
    int data = 0;
    while(true) {
        std::unique_lock<std::mutex> lck(mtx);
        while(dq.size() == 0) {
            cv.wait(lck);
        }
		data = dq.front();
        dq.pop_front();
		cout<<"deque pop :"<<data<<endl;
    }
}

int main() {
    std::thread pro(producer);
    std::thread con(consumer);

    pro.join();
    con.join();
	cout<<"exit"<<endl;
    return 0;
}
