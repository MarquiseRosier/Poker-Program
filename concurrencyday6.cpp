/*
Day 1 we learned how to make a thread,
run a function in it within another function, and 
make the enclosing function wait for the thread to finish 
executing its function with t.join!

void hello(){
	std::cout << "Hello, " << std::endl;
}

int main()
{
	std::thread t(hello);
	t.join();
}
*/

/*
Waiting for the thread by issuing a join() command is
pointless in the above scenario. The enclosing function
main() doesn't do any work, which makes it pointless to 
even thread. usually main would be doing work itself while
the thread t would be doing work too or main would 
have sent out multiple tasks to various threads and coordinated
their ending(cleaning up). 

t.join() is very brute force, either our program waits for 
the thread to finish or it doesn't, we will need other 
mechanisms to more finely control the thread. 

Additionally, t.join() cleans up the thread. after it is done
it is no longer associated with t, it is empty.

When writing threaded code, most consider all exit paths!
This can translate to verbose code, which can be cut down by using

standard Resource Acquisition is Initialization (RAII) 
to wait for a thread to complete and be safe despite exit path!

	QUIZ RECONSTRUCT RESOURCE ACQUISITION IS ININITIALIZATION methodology 
	to safely eliminate thread.*/

#include <iostream>
#include <thread>

class thread_guard
{
	public:
		explicit thread_guard(std::thread &t_) : t(t_){}

		~thread_guard(){
			if(t.joinable())
			{
				std::cout << "Thread Dying Now" << std::endl;
				t.join();
			}
		}

		thread_guard(const thread_guard&)=delete;
		thread_guard& operator =(const thread_guard&)=delete;


	private:
		std::thread &t;	
};

void func(){std::cout << "Hello I'm Marquise " << std::endl;}

int main()
{
	std::thread t(func);
	thread_guard g(t);

	operator<<(operator<<(std::cout, "Thread Finished Running, Goodbye"), " \n");
}

/*
We msut watchout for detached threads, once detached it is no longer
possible to get a handle on them! Hence, it is no longer
possible to wait on them to complete. 

Detached threads run in the background, and ownership and control
is passed over to the c++ runtime library!

Detached threads also called daemon threads..they might run for
entireity of hosting application.

YOu can detach a thread and run it in the background as a daemon 
if you delete the std::thread object to which it is tied or you 
call the std::thread detach() member function!

Joinable() also helps signify if you can detach from a thread
if it isn't joinable it is already detached or joined!

*/