/*

Readers-Writers Problem

*/

#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include<semaphore.h>

using namespace std;

// lock on cout
mutex print_lock;
sem_t r;
sem_t w;
int value = 0;

void write(int id)
{
	sem_wait(&w);
	print_lock.lock();
	value++;
	cout<<"thread "<<id<<" write, value is: "<<value<<endl;
	print_lock.unlock();
	sem_post(&w);
}

void read(int id)
{
	sem_wait(&r);
	sem_wait(&w);
	print_lock.lock();
	cout<<"thread "<<id<<" read, value is: "<<value<<endl;
	print_lock.unlock();
	sem_post(&w);
	sem_post(&r);
}

int main()
{	
	thread t1 = thread(read,0);
	thread t2 = thread(write,1);
	thread t3 = thread(write,2);
	thread t4 = thread(read,3);
	thread t5 = thread(write,4);
	thread t6 = thread(read,5);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
}