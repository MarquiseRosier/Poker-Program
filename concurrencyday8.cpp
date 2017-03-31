#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

void some_function();
void some_other_function();
void do_work(unsigned id){std::cout << "Thread: " << id << std::endl;}


int main()
{
std::vector<std::thread> threads;
for(int i=1;i<=20;i++){
	threads.push_back(std::thread(do_work, i));
}

std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));


std::cout << std::thread::hardware_concurrency() << std::endl;
return 0;
}

/*
	Above code gave us understanding of ways to transfer 
	ownership of threeads to other threads!! 
	Now we are learnign to transfer thread ownership out of a function 
	and to a function.

	This is simple, 

	std::thread f()
	{
		void some_function();
		return std::thread(some_function);
	}

	std::thred g()
	{
		void some_other_function(int);
		std::thread t(some_other_function, 42);
		return t;
	}

	t.joinable ensures that thread hasn't already
	been joined!

	Suppose you want to spawn multiple threads to subdivide 
	the work of a function!

	std::mem_fcn(&) deduces callsignature and everything you do not have
	to do anything to understand how the callable is constructed! Best used
	when callable doesn't take any parameters.

	void do_work(unsigned id);

	void f()
	{
		std::vector<std::thread> threads;

		for(int i=0;i<20;i++){
			threads.push_back(std::thread(do_work, i));
		}

		std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));	
	}

	Now this assumes the work in each thread is independent and if
	the result of the subdivision of some work is expected than that 
	work should be in some returned value which is the data hared
	betwen the threads and worked on independently. 

	The work done by the threads is self-contained and the result
	of their operations is purely the side-effects on shared data. A return
	value of these threads operations would have to be constructed by
	the examining of the shared data after the threads terminate. We will learn
	alternative schemes for transferring results of operations between threads.

	putting threads in a std::vector is a step towards automating the 
	management of those threads: rather than creating separate variables for those
	threads and joining with them directly, they can be treated as a gruop.

	We can create a dynamic number of threads at run time instead of a 
	static amount!!

	Choosing number of threads at run_time.

	std::thread::hardware_concurrency();
	returns the number of threads that can truly run concurrently on 
	a system! This may simply be the number of CPU's
*/