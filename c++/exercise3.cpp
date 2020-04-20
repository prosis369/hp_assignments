/*

Producer-Consumer Problem

*/

#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include<semaphore.h>

using namespace std;

// lock on cout
mutex print_lock, val;
sem_t r;
sem_t w;
int value = 0;
int buffer[10];

// To Print Buffer

// void printbuffer()
// {
// 	print_lock.lock();
// 	cout<<"buffer:"<<endl;
// 	for(int i=0;i<10;i++)
// 	{
// 		cout<<buffer[i]<<",";
// 	}
// 	cout<<endl;
// 	print_lock.unlock();
// }

void producer(int id)
{
	sem_wait(&w);
	val.lock();
	buffer[value] = 100;
	value++;
	print_lock.lock();
	cout<<"thread "<<id<<" producer"<<endl;
	print_lock.unlock();
	val.unlock();
	// printbuffer();
	sem_post(&w);
}

void consumer(int id)
{
	sem_wait(&w);
	val.lock();
	value--;
	buffer[value] = 0;
	print_lock.lock();
	cout<<"thread "<<id<<" consumer"<<endl;
	print_lock.unlock();
	val.unlock();
	// printbuffer();
	sem_post(&w);
}

int main()
{	
	thread t1 = thread(producer,0);
	thread t2 = thread(consumer,1);
	thread t3 = thread(producer,2);
	thread t4 = thread(producer,3);
	thread t5 = thread(producer,4);
	thread t6 = thread(consumer,5);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
}