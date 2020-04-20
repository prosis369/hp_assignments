/*

Sleeping Barber Problem

*/

#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include<semaphore.h>

using namespace std;

// lock on cout
mutex print_lock, chair;
sem_t bar;
sem_t cus;
// number of chairs
int c = 3;

void barber()
{
    cout<<"barber is asleep"<<endl;
    sem_wait(&cus); 
    chair.lock();
    c++; 
    sem_post(&bar); 
    chair.unlock();
    cout<<"hair cut"<<endl; 

}

void customer(int id)
{
    chair.lock();
    if(c > 0) { 
          c--; 
          cout<<"barber waking up"<<endl;
          sem_post(&cus);
          chair.unlock();
          sem_wait(&bar); 
          cout<<"hair cut"<<endl;
    } else { 
          chair.unlock();
          cout<<"Customer left"<<endl;
    } 
}

int main()
{	
	thread t0 = thread(barber);
	thread t1 = thread(customer,0);
	thread t2 = thread(customer,1);
	thread t3 = thread(customer,2);
	thread t4 = thread(customer,3);
	thread t5 = thread(customer,4);
	thread t6 = thread(customer,5);

	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
}