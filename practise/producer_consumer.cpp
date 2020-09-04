#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
//#include <unistd.h>
#include <string.h>
#include <windows.h>

using namespace std;
/*
// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread

void foo() 
{
  // do stuff...
}

void bar(int x)
{
  // do stuff...
}

int main() 
{
  std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (bar,0);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
 }
*/

/*
// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex

std::mutex mtx;           // mutex for critical section

void print_block (int n, char c) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  mtx.lock();
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
  mtx.unlock();
}

int main ()
{
  std::thread th1 (print_block,50,'*');
  std::thread th2 (print_block,50,'$');

  th1.join();
  th2.join();

  return 0;
}
*/

/*
// condition_variable example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id (int id) {
  std::unique_lock<std::mutex> lck(mtx);
  while (!ready) cv.wait(lck);
  // ...
  std::cout << "thread " << id << '\n';
}

void go() {
  std::unique_lock<std::mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(print_id,i);

  std::cout << "10 threads ready to race...\n";
  go();                       // go!

  for (auto& th : threads) th.join();

  return 0;
}
*/

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void producer(deque<int> &dq) {
    while(true) {
        int data = rand() % 1000;
        std::unique_lock<std::mutex> lck(mtx);
        dq.push_back(data);
        cv.notify_all();
        Sleep(1);
    }
} 

void consumer(deque<int> &dq) {
    int data = 0;
    while(true) {
        std::unique_lock<std::mutex> lck(mtx);
        while(dq.size() == 0) {
            cv.wait(lck);
        }
        dq.pop_front();
    }
}

int main() {
    std::deque<int> dq;
    std::thread producer(producer, dq);
    std::thread consumer(consumer, dq);

    producer.join();
    consumer.join();

    return 0;
}