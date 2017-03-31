/*
Here we are learning about call signatures! We can generate 3 callable 
objects using lambdas, function objects, and plain functions!

they all have the same exact call signature which is 

f(int, int)
d(int, int)
e(int, int) and each returns int. 

The only way to differentiate between these three callable objects 
is by constructing a function table which stores pointers to 
each callable. when a program needs to execute a particular operation
it looks in the table to find which functino to call. 

Suppose you want to construct a function table! linking a symbol to 
a function poniter?

std::map<std::string, int (*)(int, int)> binops;

binops.insert("+", add);

HOWEVER!!! WE CANNOT STORE STRUCTS OR LAMBDAS in this function 
table because these things come with more data than just 
call signatures, they come with actual types!!

The Library function type solves for this!!! 

#include <functional>
1)bind
2)ref
3)plus<string> d; d(string, string), less<string>, less<*string>, etc etc
4)function

function<> with this template we specify the call signature that we want to be able to use!

function<int(int, int)>

The function type can represent all of our various callable objects

function<int(int, int)> f1 = add;
function<int(int, int)> f2 = divide();
function<int(int, int)> f3 = [](int, int)->int{return someInt;};

Suppose we have overloaded callable objects

int add(int, int){return int;}

sales_data add(const std::sales_data &a, const std::sales_data &b)



INHERITANCE-----------------------------------------------------

Base Class defines as virtual those functions it expects its derived
classes to inherit and define.

class Quote{
	public:
		std::string isbn() const;
		virtual double net_price(std::size_t n) const;
};

class Bulk_quote : public Quote{
	public:
		double net_price(std::size_t) const override;
};

We can qualify a function that is inherited as virtual with override to 
signify that we will redefine it as intended by it being called virtual
by the Base Class.

Dynamic Binding!!!

ANY NON STATIC MEMBER FUNCTION MAY BE QUALIFIED AS VIRTUAL
IF IT IS STATIC IT WILL ASSOCIATE THE FUNCTION WITH THE CLASS WHEREIN
IT IS DEFINED, THUS MEANING IT WOULD NOT DYNAMICALLY BIND BASED ON BASE 
OR SUB CLASS CALLING VIRTUAL MEMBERS THROUGH A REFERENCE OR POINTER.

member functions called virtual are deduced in run-time...
member functions that are not called virtual are deduced in compile time

static methods obey normal access control standards! 

Base::statmen();
Derived::statmen();
derived_obj.statmen();
statmen();

Base class cannot be derived by deriving class unless it is defined. 

Because data members and member functions must be inherited and this
is not possible if the inheriting class doesn't know what to inherit.

we can prevent a class from being used as a base class by following it
with final!

class NoDerived final {};

static type vs dynamic type of an object...

suppose we construct a function

class Base{
	public:
		virtual void net_price();
}

class Derived : public Base{
	void net_price() override{std::cout << "From Derived";}
}

Important facts, this has a synthesized constructor that calls
default synthesized constructor for Base!

Now we do this Quote base;

Quote has static type Quote and dynamic type Quote. 

Bulk_quote* bulkP = &base; error..we cannot convert from base to derived
Bulk_quote& bulkQ = base; error

dynamic_cast is best used when Base class has virtual functions
static_cast is best used when we know the conversion from base 
to derived is safe to override compiler.

*/

/*
	Suppose we create a Bulk_quote derived class that inherits from
	a Base class Quote!

	Suppose we want to construct pointers or references to Quote objects
	and take advantage of the dynamic type that figures out its type during run-time

	it would be like so.
	
	Bulk_quote bulk;
	Quote &item = bulk;
	Quote *something = &bulk;

	Quote item(bulk); <---This calls Quote(const Quote &); copy
	Quote item;
	item = bulk; <---- this calls Quote& operator=(const Quote &);

	What happens is that the implicit conversions are accepted!
	Or the coercions are accepted, however, they SLICE DOWN bulk_quote
	and only engage the portion of Bulk_quote inherited from Quote.

	
	Hence when we construct a Base class from a derived class
	or assign a Base Class to a derived class, 
	the derived part is simply ignored!!!

	Dynamic binding happens when a virtual member function is called
	through a reference or a pointer to a base-class type. 

	Virtual functions must always bee defined, since we don't know which 
	one we are using until run time.

	ORDINARILY IF WE DO NOT USE A FUNCTION IN A PROGRAM, WE DO NOT NEED TO 
	PROVIDE AN IMPLIMENTATION FOR IT, HOWEVER, WE MUST DEFINE EVERY VIRTUAL
	FUNCTION, REGARDLESS OF WHETHER IT IS USED BECUASE THE COMPILER HAS NO 
	WAY TO DETERMINE IF A VIRTUAL FUNCTION IS USED, AS THAT IS DETERMINED
	DURING RUN TIME!!!

	cannot override overloaded functions that have same name as virtual
	function.

	If a derived virtual function that intended to call its base-class 
	version omits the scope operator, the call will be resolved at run
	time as a call to the derived version itself, resulting in an infinite
	recursion!!!!!!

	Classes with pure virtual functions are Abstract Base Classes
	and as such cannot be instantiated. Additionally, if a Derived Class
	inherits from an Abstract Base Class without defining a pure
	virtual function therein, it itself will be an Abstract Base Class.
*/

#include <iostream>

int main()
{
	int (*fp)(int, int);

	std::cout << fp << std::endl;
}