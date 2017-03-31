/*
We are learning about callable objects and function!

Lambdas, Functions, pointers to functions, objects created
by bind

A Predicate is an expression or a statement that returns
some kind of value that can be used as a condition.
These can be Binary, Unary, or whatever!

Suppose we use a function as the predicate!

bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

difference between following two call signatures

1) const bool isShorter()
2) bool isShorter() const

1) makes sure that the returned bool in a call of isShorter
is constant! such that the return value cannot be changed.
This has an easy chance of being undone, since this function
returns by copy when we use the assignment operator without 
qualifying the calling int with const, it will call the
normal assignment operator that doesn't return a const
copy and thus allow us to change a value that was returned 
as a constant!

2)
makes sure that isShorter() cannot change any member
data unless that member data is quallified with mutable
keyword.

Lambda capture lists can qualify parameters!!!

[](){} 

If Lambdas have return statement in body, the return type is
whatever can be deduced from what is to the right of the
return statement.

You can list parameters in a capture list like so
[var1, var2, var3,...,varN](){} <--- these vars are 
being captured by value!! These parameters must be in 
enclosing function too in order to be captured.

Capture list can be qualified too!

[&var1, &var2, &var3,...,&varN](){} is capture by 
reference.

[&, var1, var2, var3,...,varN](){} captures all parameters
in enclosing function body that are not listed in the 
parameter list after the ampersand by reference. If they 
are listed in the parameter list to the right of the comma,
this implies that the parameter is to be captured by value.


[=, var1, var2, var3,...,varN](){} captures everything in the
parameter list by reference! otherwise if it is not in the 
parameter list it is captured by value by the lambda.

[=](){} captures everything by value in enclosing function
[&](){} captures everything by reference in enclosing function

Mutable Lambdas!!! Lambdas cannot change values of parameters captured
by value unless those parameters are deemed mutable. 
this is done likeso

[=]() mutable {}

Again lambdas cannot change parameters captured by value
hence why they need to be made mutable or
they need to be CAPTURED BY REFERENCE!!!

example of mutable changing of captured parameter

void fcn4()
{
	size_t v1 = 42;

	auto f = [v1] () mutable {return ++v1;}

	v1 = 0;

	auto j = f();
}
//This generates 43
DO YOU SEE IT....this lambda captured the v1 by value and
thus copied the value already. When it is changed outside the 
lambda, this doesn't effect the copy in the lambda already
so the lambda when run returns 42!

Also notice how you can get a handle on the lambda by setting
it to 

auto f = [v1] () mutable {return ++v1;}

this makes f a CALLABLE OBJECT..a callable 
object or expression is callable if we can apply the call operator
to it. so if e is a callable expression or object we can write
e(args,...,)

so 
auto f = [v1] () mutable {return ++v1;}

makes f a callable object using an auto to deduce this quality
let's not forget that lambdas create classes that 
override the call operator and also initialize arguments
in the capture list with a constructor and private 
data!

Hence, lambdas make unnamed classes and f is an unnamed object 
of that unnamed class!

we can also specify return type!

[capture list from enclosing function] 
(parameter list for unnamed classes signature of call operator)
 (-> this is to help denote return type) 
 return type {return statement along with function body} 


 You can imagine already that capture by reference
 will keep an updated captured value!

 DIRECTING THE COMPILER TO INFER THE CAPTURE LIST!

 If Lambda body contains any statement other than return
 the lambda is assumed to return void!

 Legit if a LAMBDA HAS ANY CODE OTHER THAN THE RETURN
 STATEMENT IN IT, IT WILL NOT DEDUCE THE RETURN TYPE AS ANYTHING
 EXCEPT FOR VOID!

 IF WE ARE GOING TO ADD ANYTHING OTHER THAN A RETURN STATEMENT,
 WE NEED TO SPECIFY THE RETURN TYPE IN THE LAMBDA.

 [] (int i) -> int {Whatever you want}

 Lambdas should be used only where they are required maybe once 
 or twice.

 find_if() algorithm takes a unary predicate that takes one
 argument which is the current element contained by an
 iterator of a container. 

 This unary predicate is difficult to construct using functions!

 Suppose you want someone to be able to find_if() an element
 is bigger than a they are allowed to specify and isn't 
 hard coded!

 Function can take input, but what if we want this number to be 
 from a file or from user input, it's very very difficult. 

 Consider this, how will this function store its data as a 
 predicate of the find_if() algorithm? So that you can 
 be looking for something throughout the entire traversal 
 of the container since the function keeps being called over 
 you must keep providing the size parameter which is repetitive.

 An alternative is to capture fron the enclosing function and run
 a callable object constructed by a lambda repeatedly with the same 
 captured value!!

to solve the dilemna discussed above we can use the 
new function 
1) bind 
in the #include<functional>
library!

#include <functional> also holds all the library defined
function objects which work with pointers!

Maps use the library function objects thus allowing you
to construct ordered maps of pointers.

bind(callable, args-list)

bind solves the problem above by binding parameters and 
constructing a callable object with those bound parameters.

This allows us to bind sz in the enclosing function
to a newcallable using a placeholder and referencing 
a captured parameter so that we can use a binary operator
in an algorithm that only takes unary predictes.

