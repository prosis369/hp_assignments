/*

Dining Philosopher Problem

*/

#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>

using namespace std;

// lock on cout
mutex print_lock;
mutex spoon[5];

void pick_up(int id)
{
	if(id == 0)
	{
		spoon[0].lock();
		spoon[4].lock();
		print_lock.lock();
		cout<<"thread "<<id<<" acquired both spoons"<<endl;
		print_lock.unlock();
		spoon[0].unlock();
		spoon[4].unlock();
	}
	else
	{
		spoon[id-1].lock();
		spoon[id].lock();
		print_lock.lock();
		cout<<"thread "<<id<<" acquired both spoons"<<endl;
		print_lock.unlock();
		spoon[id-1].unlock();
		spoon[id].unlock();
	}

}


int main()
{	
	thread t1 = thread(pick_up,0);
	thread t2 = thread(pick_up,1);
	thread t3 = thread(pick_up,2);
	thread t4 = thread(pick_up,3);
	thread t5 = thread(pick_up,4);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

}
