/*
	A class that inherits from a Base class cannot give friend
	access to it's base classes members, even if those members were
	said to be protected! It however, can give access to it's access 
	to a protected variable.

*/
#include <iostream>
#include <functional>

	class Base{
		friend class pal;

		public:
			Base() : prot_mem(5604){}

		protected:
			int prot_mem;

		private:
			const int t = 5003;
	};

	class Sneaky : public Base{
		friend void clobber(Sneaky&);
		friend void clobber(Base&);

		private:
			Base b;
		int j;
	};

	class pal{
	public:
		void h(const Sneaky &s){std::cout << s.prot_mem << std::endl;}
	};

	void clobber(Sneaky& s){s.j = s.prot_mem ; std::cout << s.prot_mem << std::endl;}

	int main()
	{
		Sneaky sk;
		Sneaky jk;
		pal hal;
		std::less<Sneaky*> stdLess;

		Sneaky *s = &sk, *t = &jk;

		std::cout << std::less<Sneaky*>()(s, t) << std::endl;

		clobber(sk);
		hal.h(sk);

		return 0;
	}

/*
	What this says is that friends of a class can access
	the inherited part of a derived class that they are friends
	with but they cannot access the inherited classes 
	protected, or private data on their own accord.

*/

/*------------------------------PUBLIC, PROTECTED, PRIVATE INHERITANCE-
class Base
{
	public:
		void pub_mem();
	protected:
		int prot_mem;
	private:
		char priv_mem;
};

struct Pub_Derv : public Base{
	int f() {return prot_mem;}

	char g() {return priv_mem;}	
};

struct Priv_Derv : private Base{
	int f1() {return prot_mem;}
	// Private Derivation doesn't affect deriving class access.	
	//Deriving class access is controlled by the Base Class
	//Access specifier.
	//this cannot access private members!
};

The purpose of derivation access specifiers is to control the 
access that USERS of the derived class have to the members 
inherited from the BASE that comprise the Derived through inheritance

Function pub_mem() cannot be accessed using dot notation anywhere
other than within the derived class, because it is private to all
USERS of the derived class. 

For ecample after we construct those classes, we try to call
Priv_Derv d1;
d1.pub_mem();

we make this call in the int main function which is not within the
derived class 

Also if you make two structs

struct Derived_from_Private : public Priv_Derv{
	
int use_base(){return prot_mem;}
//THIS WILL FAIL BECAUSE although this struct inherits
//From the derived class of the base class... 
prot_mem a protected member....which itself inherited
that member from the base class...the inheritance access 
specifier was made private and so when the struct inherits the derived 
class, the base class component of the derived class are private
to any users of the derived class!!
};

THIS PART OF ME IS PRIVATE...BUT I CAN STILL ACCESS MY PRIVATE PART!

we can specify access for particulr members of Base elements in a derived
class by employing the USING keyword so that users of the derived
class can access only certain parts of the base class that comprises
the derived class.

Can only provide using clauses for members it is allowed to access

private inheritance access specifier by default if we don't include one.

You can only use derived to base conversion where derived access specifier where
the derived access specifier is public.

user code cannot use conversion if D inheris from B privately or protectedly

What if we don't make base class destructor virtual and dnt define 
destructors for derived classes, that means when a pointer to a base
has a dynamic type when you destroy it, it will call the wrong destructor
and if that destructod deletes pointer data, the consequences can be 
really bad on a Derived class that depends on the base data.

imagine that the derived part is still intact, and we delete only the 
base part using the base destructor....smh.

However, virtual destructors cause the compiler to not create 
synthesized move constructors, so if you want a move assignment operator
and a move constructor you have to define them in tandem with 
virtual destructors.

Suppose we have Base Class and Derived Class, if we define Copy 
and move constructors and assginment operators we can pass the 
copy and move constructors reference to a derived object to be 
copied to the base copy or move constructor..like so

class Base{
	Base(const Base&);
	Base(Base &&);	
	Base& operator=(const Base&);
	Base& operator=(Base &&);
	virtual ~Base();
}; 

class Derived : private Base{
	Derived(const Derived& d) : Base(d){}
	Derived(Derived &&d) : Base(std::move(d)){}	
	Derived& operator=(Derived &&d){
		Base::operator=(std::move(d));
	}
	Derived& operator=(const Derived &d){
		Base::operator=(d);
	}
	~Derived();
};

This is how it would look you see!!

Containers and inheritance, to store Base and Derived
constructs, we should pass pointers to Base Class in order for dynamic
allocation to take place within the container.

#inlcude <vector>

std::vector<Base> basket;


basket.push_back(base1);

basket.push_back(derived1); 
//THE ABOVE PUSH_BACK CALL SHOULD WORK BECAUSE DERIVED1 IS A 
BASE OBJECT TOO. 

BUT THIS WILL FAIL AND USE THE STATIC TYPE....SO INSTEAD 
MAKE A VECTOR OF SHARED POINTERS

std::vector<std::shared_ptr<Base>> basket;

and this can store derived classes in the Base class static type.

TEMPLATED PROGRAMMING	

template <typename T>
int compare(const T &v1, const T &v2)
{
	if(v1 < v2){return -1;}
	if(v2 < v1){return 1;}
	return 0;
}

in a template definition the template parameter list cannot be
empty.

We provide a placeholder type T in the function template this 
type is determined either implicitly or explicitly. It is implicit 
because the compiler determines the type based on how the function
template is used. 

So by calling 
compare(1, 0) it knows that T is type int because the parameters
in compare are ints.

Compiler uses the deduced template parameters to instantiate a specific
version of the function for us. When it instantiates a template
it creates a new instance of the template using the actual template arguments
in place of the corresponding template parameters. 

if we do two calls

std::vector<int> vec1, vec2;
int v1, v2;

and we run compare(vec1, vec2)
This has template instantiation of

int compare(std::vector<int>, std::vector<int>)
{
	
}

nontype templates use nontypes like values instead 
of class or typename. 

template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char(&p2)[M])
{
	return strcmp(p1, p2);
}

This will deduce N=3 nd M=4 because compiler inserts null 
terminator at the end of a string literal.

constexpr and inline function templates!

template <typename T> inline T min(const T&, const T&);

THIS IS INCORRECT
inline template <typename T> T min&const T&, const T&);
THIS IS INCORRECT ^^^^

there can be types that do not allow copying, these types can
use our function template because our function template 
passes by const reference! it references lvalue and also makes it 
so that we cannot change it!

This pushes for Type independence, in fact if we were true to the
type independence methodology, we would have used std::functional::less<T>
because this allows us to also compare pointers!

Templated programming should try to minimize the number of requirements
on the arguments provided! They shouldn't have to have 
a certain symbolic operation defined...or have to be static typed
etc etc.


We are going to make a generic class using class templates

template <typename T> class Blob{
	public:
		typedef T value_type;
		typedef typename std::vector<T>::size_type size_type;
		Blob();
		Blob(std::initializer_list<T> il);

		//size of Blob
		size_type size() const {return data->size();}	
};

When instantiating a class template, we need to give explicit template arguments

Instantiating Blob<int> makes sure value_type is now int
the vector is a vector of int, elements are pushed into the inte vector
and they themselves are ints..this is a whole instance of the class template
predicated on int explicit template arguments.

compiler will instantiate a class that is equivalent to 

template  <> class Blob<int>
{
	typedef typename std::vector<int>::value_type value_type;
	Blob();
	Blob(std::initializer_list<int> il);

	etc etc 
	.
	.
	.	
};

member functions defined in template body are implicitly inline!

name of a class generated from a class template must come with template
arguments!

template <typename T>
ret_type Blob<T>::funct_name(param-list){}

initializer_list<int> in a constructor allows us to use following
notation
Blob<string> b = {"Marquise", "Joelle", "Tryton", "Midenlex", "Kamari"};

inside scope of a class template we can refer to class without template 
arguments, but outside of the class where we can define members
we must refer to the class with template arguments. 

thus, member definitions outside of classes must refer to class name
with template arguments, but then once after we make function 
signature we are within class scope!

Suppose we want to declare 

a constant expression is an expression that is constant and who's
value is determined at compile time. A literal is a constant 
expression. A const object that is initialized from a constant expression 
is also a constant expression.

const int max_files = 20;
^ this is constexpr

const int limit = max_files +1;
limit is constexpr


*/