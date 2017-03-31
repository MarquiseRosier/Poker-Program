/*
Problems with sharing data between threads is due to modifying data!!!
If all shared data is read-only there is no problem, since the data read
by one thread is unaffected by whether or not another thread is reading it
HOwever, if data is shared between threads, and one or more threads start
modifying data, there is a lot of potential for trouble. In this case you 
must take care to ensure that everything works out OK. 

Invariants!! Statements that are always true about a particular data structure
such as this variable contains the number of items in the list". These
invariants are often broken during an update, especially if the data structure 
is of any complexity or the update requires modification fo more than one
value.

identify the node to delete (N)
update the link from teh node prior to N to point to the node after N
update the link after node N to point to the node prior to node N
delete the node N

If one thread is reading the list whilst another is deleting a node, 
it is possible for the reading thread to read a list with a partially
deleted node. The invariant that if a node is deleted, the nodes
before and after this deleted node must point to one another and not the 
node we intend to delete is broken....so if this invariant isn't upheld while
a thread is reading the list, we are giving the reading thread a corrupted data
structure which can have implications on our program. Whatever the implication or
outcome of this corrupted data, this is a bug commonly known as 

A RACE CONDITION!!!!

A RACE CONDITION IS WHERE THE OUTCOME OF A SUCCESSFUL THREAD EXECUTION DEPENDS
ON WHETHER ONE THREAD RUNS BEFORE THE OTHER THREAD! SO IN THIS CASE 
THE SUCCESSFUL RUNNING OF THE READING THREAD IS PREDICATED ON THE READING THREAD
RUNNING AFTER THE DELETING THREAD.


OR SUPPOSE YOU GO TO A MOVIE THEATER AND WANT TO BUY TICKETS. THERE ARE MULTIPLE
SELLERS SELLING TICKETS. SOMEBODY WANTS TO BUY TICKETS FOR THE SAME MOVIE AS YOU,
AND THERE ARE VERY FEW SEATS LEFT. WHETHER YOU GET A TICKET, OR WHAT TICKET YOU GET
DEPENDS ON WHO BUYS TICKETS FIRST, THIS IS A RACE CONDITION.

IN CONCURRENCY A RACE CONDITION IS ANYTHING WHERE THE OUTCOME DEPENDS ON THE RELATIVE
ORDERING OF THE EXECUTION OF OPERATIONS ON TWO OR MORE THREADS, THE THREADS RACE TO 
PERFORM THEIR RESPECTIVE OPERATIONS. THREADS MAY RACE TO PERFORM THEIR RESPECTIVE 
OPERATIONS BECAUSE ALL OUTCOMES ARE ACCEPTABLE, IT IS WHEN ONE PARTICULAR OUTCOME 
BREAKS THE INVARIANTS ON THE DATA THAT WE HAVE A PROBLEM. RACE CONDITION IS USUALLY
AN ALIAS TO A PROBLEMATIC RACE CONDITION. C++ STANDARD ALSO DEFINES THE TERM 

-------------DATA RACE--------------
TO MEAN THE SPECIFIC TYPE OF RACE CONDITION THAT ARISES DUE TO CONCURRENT 
MODIFICATION TO A SINGLE OBJECT; DATA RACES CAUSE THE DREADED UNDEFINED BEHAVIOR.

PROBLEMATIC RACE CONDITIONS USUALLY TURN UP WHEN TWO OR THREE PIECES OF DATA MUST
BE MODIFIED, WHICH REQUIRES TWO OR THREE SEPARATE INSTRUCTIONS. THIS RUNS THE RISK 
THAT ONLY ONE IS EXECUTED BEFORE ANOTHER THREAD RUNS ON DATA THAT DOES NOT UPHOLD THE
INVARIANT.

THE PROBLEM DEPENDS ON PROBLEMATIC EXECUTION SEQUENCE OCCURING AND THE PROBABILITY OF A 
PROBLEMATIC SEQUENCE OF OPERATIONS OCCURING INCREASES WITH THE NUMBER OF TIMES YOU 
RUN THE MULTI-THREADED CODE! SO TESTING IS CRUCIAL.

---------------------------------------------------------------------------------
-------------------------------------------------------------------------
PROTECTING SHARED DATA WITH MUTEXES..

Wouldn't it be cool to mark all pieces of code that access the data 
structure as mutually exclusive, so that if any thread was running one of them
any other thread that tried to access that data structure had to wait until
the first thread was finished?

Thus a thread cannot see a broken invariant unless it was that thread doing
the modifying. 
Mutex = synchronization primitive = mutual exclusion. 

Before accessing a shared data structure, you lock the mutex associated with 
the data, and when you're done accessing the data structure you unlock the mutex.

The thread library then ensures that once one thread has locked a specific
mutex, all other threads that try to lock the same mutex have to wait until the thread
that successfully locked the mutex unlocks it. This ensures that all threads see
a self-consistent view of the shared data, without any broken invariants.

Mutexes are general of data protection mechanisms, but must construct them to prevent
deadlocs nd race conditions inherent in interface. Mutexes also sometimes protect
too little or too much data. 

#include <list>
#include <mutex>
#include <algorithm>

RAII idiom for a mutex, you should not yourself lock and unlock a mutex, 
as you have to remember to unlock it after every possible exit path from a function
instaed use std::lock_guard so that upon lock_guard construction a mutex is locked
and upon destruction the mutex is destroyed in the lock_guards destructor. 

std::lock_guard calls std::mutex::unlock() when the lock_guard runs out of scope
std::lock_guard calls std::mutex::lock() when the lock_guard is constructed!

#include <list>
#include <thread>
#include <mutex>
#include <algorithm>

Do not pass references or pointers to data that is to be locked with mutex
also do not return pointers or references.

Call to user-defined function passing private data is first error
passing malicious function to bypass protection And then calling 
do_something on the data without mutex being locked.

granularity = the size of a task in threaded programming, too small granularity
implies protection doesn't cover entiriety of an operation.

You want to protect enough and not too little, 
sometimes when you apply a lock on mutexes for two or more operations
instead of racing to be first, they are waiting on one another, so neither makes 
any progress...


trying to lock a mutex that is already locked is undefined behavior.std::lock 
ensures that mutexes in both instances 

if you need to get multiple locks, do them as a single instructin using 
std::lock(mutex1, mutex2);
std::lock_guard(lhs.m, std::adopt_lock);
std::lock_guard(rhs.m, std::adopt_lock);

*/

#include <thread>
#include <mutex>

int main()
{
	std::hierarchical_mutex m;
	return 0;
}