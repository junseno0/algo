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
#include <semaphore.h>

using namespace std;

std::mutex mtx;
std::condition_variable cv;
bool ready = false;
std::deque<int> dq;
sem_t sem_input;
sem_t sem_output;

void producer() {
	int data = 0;
    while(true) {
		sem_wait(&sem_input);
		{
			mtx.lock();
        	data = rand() % 1000;
        	dq.push_back(data);
			mtx.unlock();
		}
		cout<<"deque push ------->"<<data<<endl;
		sem_post(&sem_output);
        sleep(1);
    }
} 

void consumer() {
    int data = 0;
    while(true) {
		sleep(1);
		sem_wait(&sem_output);
		{
			mtx.lock();
			data = dq.front();
			dq.pop_front();
			mtx.unlock();
		}
		cout<<"deque pop :"<<data<<"<-------"<<endl;
		sem_post(&sem_input);
    }
}

int main() {
	sem_init(&sem_input, 0, 64);
	sem_init(&sem_output, 0, 64);
	cout<<"multi producer and multi consumer"<<endl;
	
    std::thread pro1(producer);
    std::thread pro2(producer);
    std::thread con1(consumer);
    std::thread con2(consumer);

    pro1.join();
    pro2.join();
    con1.join();
    con2.join();

	sem_destroy(&sem_input);
	sem_destroy(&sem_output);

	cout<<"exit"<<endl;
    return 0;
}
