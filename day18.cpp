#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

template <typename T, class Container = std::vector<T>> class practiceCount{
	typedef typename Container::size_type size_type;
	typedef T value_type;
	typedef Container container;

public:
	practiceCount(std::initializer_list<value_type> il) : thisContainer(il){}

	void countElements(){
		for(size_type counter = 0; counter < thisContainer.size(); counter++)
		{
			std::cout << thisContainer[counter] << std::endl;
		}
	}

private:
	Container thisContainer;
};

int main()
{
	std::initializer_list<int> il = {1, 345, 232, 654, 843, 993};

	practiceCount<int> pC= {1, 345, 232, 654, 843, 993};

	pC.countElements();
	/*
		Above code indicates that we can construt a vector with an initializer_list.
	*/

	/*
		Class Templates, are great. They allow us to instantiate a class template with 
		a type that may not support an operation. This is because templates do not instantiate
		members until those members are called upon, so templates do not know if a type will not 
		meet the requirements of the template..

		Suppose you make a class template for a shopping cart that requires the run operation
		be defined for the type you instantiate the class template around. This member function isn't
		called anywhere in the code....


		Suppose you instantiate a class template for shopping cart with an Elderly Disabled person as 
		the class argument or type....
		They do not have teh operation of running defined on them..but everythign else checks out..

		Everything else will work smoothly until you instantiate(by calling) a member function that
		depends on the run operation being defined for the class argument type.

		/*------------------------BY DEFAULT A MEMBER OF AN INSTANTIATED CLASS TEMPLATE IS INSTANTIATED ONLY IF 
								THE MEMBER IS USED-------;

		TEMPLATE TO TEMPLATE FRIENDSHIP
		ONE-TO-ONE
		THESE FRIENDSHIPS ESTABLISH FRIENDSHIP BETWEEN CORRESPONDING TEMPLATES.

		Our Blob class should declare friendship to the BlobPtr class template and a template version
		of the Blob equality operator too. 


		In order to specify a specific instantiation of a template, it must include the template's template parameter
		list.

		THESE ARE CALLED FORWARD DECLARATIONS, COMPILER DOESN'T KNOW THAT THESE ARE TEMPLATES 
		YET, WE MUST INFORM IT THAT HEY THESE ARE TEMPLATES AND THEY WILL UNDERGO TEMPLATE FRIENDSHIP
		REMEMBER IF A CLASS USES A TEMPLATE, IT MUST BE DEFINED SOMEWHERE. IF WE WANT TO BE ABLE TO 
		USE OTHER TEMPLATED CLASSES IN DEFINING A TEMPLATE CLASS, THEY MUST BE PRESENT SOMEWAY AND 
		THAT IS WITH FORWARD DECLARATIONS.

		ACTUALLY FORWARD DECLARATIONS ARE ONLY NECESSARY IN ORDER TO BEFRIEND CERTAIN INSTANCES
		OF A CLASS TEMPLATE. 

		template <typename> class BlobPtr;
		template <typename> class Blob;
		template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);

		Giving functions and operators template arguments like classes, helps us restrict
		instances we want associated with a certain template in spreading template friendship. 

		so 

		template <typename T> class Blob{
			friend class BlobPtr<T>;
			friend bool operator==<T>
				(const Blob<T>&, const Blob<T>&);

		};

		A cLASS MAY MAKE EVERY INSTANTIATION OF A TEMPLATE ITS FRIEND TOO, forward declaration is 
		not necessary in those cases.

		template <typename> Pal;

		class C{
			friend class Pal<C>; // only instantiations of the class template Pal that are instantiated
			//with respect to C have access to nonpublic members of C. 
		
			template <typename T> friend class Pal2;
		};

		template <typename> Pal;

		template <typename T> class C2{
			friend class Pal<T>;
			//This is one-to-one friendship. C2<int> gives friend access to Pal<int>
			//C2<std::string> gives friend access to Pal<std::string>

			template <typename X> friend class Pal2;
			//All instances of Pal2 are friends with all instances of C2. 

			friend class Pal3;
			//a nontemplate class that is friends with all instances of C2
			

			IN ORDER TO GET SPECIFIC WITH FRIEND DECLARATIONS OF TEMPLATED FRIENDS, 
			PRIOR DECLARATION OF THESE CLASSES AS TEMPLATES IS NECESSARY. 

			Befriending the Template's own type parameters!!!!!

			under C++11 we can allow the type of a class template to befriend the class
			or class template giving friend access. 

			template<typename Type> class Bar{
				friend Type;
			};

			Thus if we have a Bar<Foo> Foo is a friend thereof. 
			If we have a Bar<Sales_data> Sales_data is a friend thereof.

			an instantiation of a class template defines a type that can be given an alias
			we can use typedef!!!

			typedef Blob<std::string> StrBlob;

			you can define a type alias using c++11

			template <typename T> using twins = pair<T, T>;

			we cannot reuse template parameter names, and also the template parameter hides
			names outside of the template scope, so it takes over a name. goo

			compiler usually knows whether it is dealing with static member or type member. 
			In ordinary non-template code, the compiler has access to class definitions. Thus it knows
			whether a type accessed through the scope operator is a type or a static meber. 

			For example, f::value_type can be from defining

			template <typename V> class f{
				typedef V value_type;
			};

			Or f::value_type can be from

			template <typename V> class f{
				public:
					static int value_type;
			};

			this too would be accessed using f::value_type;

			However, the compiler does not know this because templates do 
			not produce any code at all they are nothing but templates on how things should be
			instantiated, it takes an actual instantation to tell us specific information because
			only then is code generated. So when we want to use something with that syntax in another file
			or in the same file, the compiler cannot with any confidence whatsoever say if 

			f::value_type * p;

			is a multiplicative expression multipyling f::value_type and p or if it is a type declaring a pointer
			p. 

			Also language inherently guesses, presumably because it is cheaper, that this is merely a multiplication.
			Also probably because multiplication is a built in operation it can throw an error if it isn't defined
			presuming it's a class though is a costly mistake that has no real error. 

			Hence, we need to preempt this and provide this information by saying explicitly that hey, this is a
			typename!

			typename f::value_type *p;

			So that this confusion cannot exist.

			template <typename T>
			typename T::value_type top(const T& c){
				if(!c.empty()){
					return c.back();
				}
				else
					return typename T::value_type();
			}
		};

		either an ordinary class or a class template may have members that are templates too!!!
		member templates are what they are called and they cannot be virtual!!!!!!

		This is better than passing all the arguments with the class template instead of

		template <typename T, typename it>
		class Blob{
			Blob(it beg, it end);
		};

		which necessitates constructing an instance of Blob like this

		Blob<T, it> blobObject(i.beg, i.end)

		or we can construct our blob object like

		Blob<T> blobObject(templateParameters, templateParameters);

		and run our function template 
		with the necessary parameters.

		Thus we would do 
		template <typename T> class Blob{
			template <typename Iter> Blob(Iter begin, Iter end);
		};

		If we define this outside of the class scope, and it is not inline defined, we must refer
		to class template parameter first and then function template parameters secondly

		So 
		template <typename T>
		template <typename It>
		Blob<T>::Blob(It begin, It end) : {}

		for templates, static members are associated with every instance of the template!! 

		Suppose you have 

		template <typename T> class Blob{
			public:
				static int objCount();
			private:
				static int count;
		};

		outside of class declaration scope, we would refer to this as

		template <typename T>
		int Blob<T>::count = 0;

		template <typename T>
		int Blob<T>::objCount(){
			return count;
		}

		Suppose we create a 
		Blob<int>
		Blob<double>
		Blob<std::string>

		These each would have their own objCount static member referenced likeso

		Blob<int>::objCount;
		Blob<double>::objCount;
		Blob<std::string>::objCount;

	
	*/
}

