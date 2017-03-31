#include <iostream>
#include <thread>
#include <functional>
#include <algorithm>
#include <iterator>

void print_something(int numb)
{
	std::cout << numb << std::endl;
}

void print_itr(std::thread &&itr)
{
	std::cout << itr.get_id() << std::endl;
}

int main()
{
	std::vector<std::thread> threads;
	for(int i=1;i<=10;i++){
		threads.push_back(std::thread(print_something, i));
	}

	std::for_each(threads.begin(), threads.end(), print_itr);

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	return 0;
}


/*template<typename Iterator,typename T>
struct accumulate_block
{
void operator()(Iterator first,Iterator last,T& result)
{
result=std::accumulate(first,last,result);
}
};
template<typename Iterator,typename T>
T parallel_accumulate(Iterator first,Iterator last,T init)
{
unsigned long const length=std::distance(first,last);
if(!length)
return init;
unsigned long const min_per_thread=25;
unsigned long const max_threads=
(length+min_per_thread-1)/min_per_thread;
#1
#2
unsigned long const hardware_threads=
std::thread::hardware_concurrency();
unsigned long const num_threads=
#3
std::min(hardware_threads!=0?hardware_threads:2,max_threads);
unsigned long const block_size=length/num_threads; #4
std::vector<T> results(num_threads);
std::vector<std::thread> threads(num_threads-1); #5
Iterator block_start=first;
for(unsigned long i=0;i<(num_threads-1);++i)
{
Iterator block_end=block_start;
std::advance(block_end,block_size);
threads[i]=std::thread(
accumulate_block<Iterator,T>(),
block_start,block_end,std::ref(results[i]));
block_start=block_end;
}
accumulate_block()(block_start,last,results[num_threads-1]);
#6
#7
#8
#9
std::for_each(threads.begin(),threads.end(),
std::mem_fn(&std::thread::join)); #10
return std::accumulate(results.begin(),results.end(),init); #11

*/
/*
	for(int i=0;i<(num_threads-1);i++)
	{
		threads[i] = std::thread(
		accumulate_block()(block_start, block_end, std::ref(result[i]));

	} 


	std::advance(iterator_position, number);
	//This advances an iterator by number from the offset

	so now the thread will run
	accumulate_bloeack(block_start, block_end, result[i])

Thread Identifiers!!!

std::thread::id they can be retrieved in two ways. 

Can be obtained by calling get_id() on a thread!
If the thread doesn't have an associated thread of execution, 
get_id() returns a default constructed std::thread::id object 
that indicates "not any thread". 

std::thread::id identifiers define complete set of comparison operators
thus allowing them to be stored as keys in associative containers.

standard library defines std::hash<std::thread::id> so that values 
can be used as keys in the new unordered associative containres too!!!





	
*/