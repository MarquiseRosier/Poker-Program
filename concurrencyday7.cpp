#include <iostream>
#include <thread>

int main()
{
	/*
		We can pass parameters to a function that we want to run
		in a thread by just passing extra parameters to the
		threads constructor like so...

		std::thread t(function, param1, param2, ... ,)
		However, this has fundamental problems. 

		Biggest problem with threads is losing data being used in 
		a thread before the thread is finished, thus causing 
		undefined behavior. 

		assume we construct a program.

		void f(int i, const std::string &s);

		void oops(int some_param)
		{
			char buffer[1024];
			sprintf(buffer, "%i", some_param);
			std::thread(f, 3, buffer);

			What happens is that this std::thread constructor
			simply copies buffer into local memory to be used 
			in executing f. What can happen though 
			is that there is a significant risk that 
			oops can stop running as the thread is 
			not dependent on oops anymore. If oops 
			decides to finish running, we have a dangling pointer
			as it will surely wipe out the buffer pointer. 

			This is why before we continue we should cast the char buffer
			to string and force a copy of all relevant and necessary data 
			to be safely included in the thread.
		}
	return 0;
}

Bind and Thread constructors are more or less the same, std::bind 
takes a callable object and parameters all as arguments to its
own construction. 

PROBLEM CAN EMERGE FROM PASSING ARGUMENTS INTO THREAD THIS WAY HOWEVER

YOU MIGHT WANT TO PASS A VARIABLE BY REFERENCE TO THE 
CALLABLE GIVEN TO THREAD....HOWEVER...THREAD COPIES THE PARAMETERS
THAT YOU WANT IT TO PASS TO THE CALLABLE INTO ITS LOCAL MEMORY!

THUS, WHEN IT FEEDS THE FUNCTION A VARIABLE AND THAT CALLABLE
TAKES IT BY REFERENCE, IT IS REFERENCING A LOCAL COPY OF THE VARIABLE
WITHIN THE THREAD AND NOT THE COPY INTENDED!

THIS MANDATES PASSING THE PARAMETER INTO THREAD USING THE 
std::ref() utility defined in #include <functional>!

We can also pass function pointers to the thread constructor...
in fact we can pass a function address and the address of an instance
of the class wherein some function is defined.

Suppose we have the following class

class X
{
	public:
		void do_lengthy_work();
};

X my_x;

HERE IS THREADS CONSTRUCTION WITH REFERENCE TO FUNCTION AND TO AN INSTANCE
OF THE CLASS WHEREFROM TEH CALLABLE OBJECT HAILS.

std::thread t(&X::do_lengthy_work, &my_x);

This will run the function as my_x.do_length_work(); on the new thread!

You can also supply arguments from the third parameter position in the thread
constructor!!!

What about when the arguments cannot be copied, but can only be moved?

An example is the std::unique_ptr which allows only one std::unique_ptr to 
access an object at any given time. When that instance is destroyed, the pointed 
to object is deleted!

The move constructor and move assignment operator allows ownership of 
to be transferred between std::unique_ptr instances. This transfer leaves
source std::unique_ptr with NULL pointer. This moving of values allows
ojects of this type to be accepted as function parameters or returned
from functions.

