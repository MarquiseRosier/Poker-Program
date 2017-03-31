#include <iostream>

class Practice{
public:
	Practice();
	Practice(const Practice&);
	Practice(Practice&&) noexcept; 
	/*Since Move Constructor doesn't allocate any resources,
	it usually won't throw any exceptions! The compiler however
	will check all constructors and all code for the possibilty 
	of an exception. To prevent this extra overhead, we can include
	the {noexcept} keyword after the parameter list and before the 
	initiailization list of the constructor.
	Although move operations do not ordinarily throw exceptions
	they are allowed to do so. Hence why we have to tell the compiler
	to ignore the possibility of a throw.*/

private:


protected:


};