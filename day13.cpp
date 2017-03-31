/*
	Ordinarily you can call functions on rvalues or lvalues. lvalues are
	variables that store instances of objects rvalues are unstored...object 
	instances without handles.

	People can change the value of a function. for example
	changing the returned value of concatenation 

	s1 + s2 = "wow";
	when std::string s1 = "I love animals", s2="I hate meat";
	s1 + s2 = "wow"; is totally valid and if we want to prevent this
	we can force function to generate a return value that must be 
	the left hand operand can be forced to be an lvalue

	qualifying functions with ampersand allow us to either
	run a function on a lvalue or on a rvalue.

	class Foo {
	public:
		Foo &operator =(const Foo&) &;
	};

	Foo &Foo::operator=(const Foo &rhs) &
	{
		return *this
	}

	
*/

