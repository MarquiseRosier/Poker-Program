#include <thread>
#include <iostream>

void printSomething(void){operator<<(std::cout, "Hello, Threaded World");}

int main()
{
	std::thread t(printSomething);
	t.join();
	return 0;
}