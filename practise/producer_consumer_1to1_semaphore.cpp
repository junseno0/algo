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
    while(true) {
        int data = rand() % 1000;
		sem_wait(&sem_input);
        dq.push_back(data);
		cout<<"deque push ------->"<<data<<endl;
		sem_post(&sem_output);
        sleep(1);
    }
} 

void consumer() {
    int data = 0;
	sleep(1);
    while(true) {
		sem_wait(&sem_output);
		data = dq.front();
		dq.pop_front();
		cout<<"deque pop :"<<data<<"<-------"<<endl;
		sem_post(&sem_input);
		sleep(1);
    }
}

int main() {
	sem_init(&sem_input, 0, 64);
	sem_init(&sem_output, 0, 64);
	cout<<"semaphore init for input and output"<<endl;
	
    std::thread pro(producer);
    std::thread con(consumer);

    pro.join();
    con.join();

	sem_destroy(&sem_input);
	sem_destroy(&sem_output);

	cout<<"exit"<<endl;
    return 0;
}
