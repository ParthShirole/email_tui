### Lambda expression in C++

C++ 11 introduced lambda expression to allow us write an inline function which can be used for short snippets of code that are not going to be reuse and not worth naming. In its simplest form lambda expression can be defined as follows:

```
[ capture clause ] (parameters) -> return-type  
{   
   definition of method   
} 
```

```cpp
#include <iostream>

using namespace std;

int main()
{
    auto func = [] () { cout << "Hello world"; };
    func(); // now call the function
}
```

A lambda expression can have more power than an ordinary function by having access to variables from the enclosing scope. We can capture external variables from enclosing scope by three ways :
      Capture by reference
      Capture by value
      Capture by both (mixed capture)

Syntax used for capturing variables :
- [&] : capture all external variable by reference
- [=] : capture all external variable by value
- [a, &b] : capture a by value and b by reference


C++ 14 buffed up lambda expressions further by introducing whats called a generalized lambda. To understand this feature lets take a general example. Suppose we create a lambda function to return the sum of two integers. So our lambda function would look like

`[](int a, int b) -> int { return a + b; }`

Lets say, *a* and *b* are passed as double... so now we would have to create another lambda function.


But, is C++ that dumb?
No, right!

Here comes `auto` keyword to our rescue. It initializing the data type of a variable dynamically. 

Code snippet:-

`[](auto a, auto b) { return a + b; }`


#### Example Program

```cpp
// Cpp program to demonstrate
// generalized lambda expressions
#include <iostream>
#include <string>

using namespace std;
int main()
{

	// Declare a generalized lambda and store it in sum
	auto sum = [](auto a, auto b) {
		return a + b;
	};

	// Find sum of two integers
	cout << sum(1, 6) << endl;

	// Find sum of two floating numbers
	cout << sum(1.0, 5.6) << endl;

	// Find sum of two strings
	cout << sum(string("Geeks"), string("ForGeeks")) << endl;

	return 0;
}
```
---
### Command line arguments in C/C++

The most important function of C/C++ is main() function. It is mostly defined with a return type of int and without parameters :

```cpp
int main() { /* ... */ } 
```

We can also give command-line arguments in C and C++. 

Command-line arguments are given after the name of the program in command-line shell of Operating Systems.
To pass command line arguments, we typically define main() with two arguments : first argument is the number of command line arguments and second is list of command-line arguments.

```cpp
int main(int argc, char *argv[]) { /* ... */ }
```

- argc (ARGument Count) is int and stores number of command-line arguments passed by the user including the name of the program. So if we pass a value to a program, value of argc would be 2 (one for argument and one for program name)
- The value of argc should be non negative.
argv(ARGument Vector) is array of character pointers listing all the arguments.
- If argc is greater than zero,the array elements from argv[0] to argv[argc-1] will contain pointers to strings.
- Argv[0] is the name of the program , After that till argv[argc-1] every element is command -line arguments.

---

## Pointers in C/C++
Pointers are symbolic representation of addresses. They enable programs to simulate call-by-reference as well as to create and manipulate dynamic data structures.

##### How to use a pointer?

- Define a pointer variable
- Assigning the address of a variable to a pointer using unary operator *(&)* which returns the address of that variable.
- Accessing the value stored in the address using unary operator (*) which returns the value of the variable located at the address specified by its operand.

Example snippet:- 

```cpp
int var = 20; 
      
        //declare pointer variable    
    int *ptr; 
      
    //note that data type of ptr and var must be same
    ptr = &var;    
```

#### There are 3 ways to pass C++ arguments to a function:

1. call-by-value
1. call-by-reference with pointer argument
1. call-by-reference with reference argument

let's first recall what's call by value and call by reference.

lets say there's a function which takes in two integers arguments and swaps there value. 

```cpp
swap(int a, int b)
{
	x=20;
	y=10;
}

int x=10,y=20;
swap(x,y);
printf(x,y);

```

Here, we are passing the values of x and y to the function. (i.e. the **value** of x and y are _copied_ to a and b.) Therefore, one the function call ends, the copied variables are destroyed.

By destroyed i mean, the **stack** frame in RAM, where this copy was generated gets cleared by the computer.

Basically, the function operated on the copies of the varibles and not on the same variables.

This was _Call By Value_


In Call by Reference, we pass the address of the variable to the function; cuz of which no copies are generated and the changes are directly reflected on the original variables.

For this method, we have to use pointers.

```cpp
int swap(int *ptr1,int *ptr2)
{
	*ptr1=20;
	*ptr2=10;
}

int x=10,y=20;
swap(&x,&y);
prinf(x,y);
```

`&x` passes not the value of the variable 'x' but its address.
>this is known as "_referencing_"

`*ptr1` gives us the "value" of the location it points to.
>this is known as "_dereferencing_"


//more about smart pointers later

---

### Namespace in C++

In each scope, a name can only represent one entity. So, there cannot be two variables with the same name in the same scope. Using namespaces, we can create two variables or member functions having the same name.

```cpp
// Here we can see that more than one variables
// are being used without reporting any error.
// That is because they are declared in the
// different namespaces and scopes.
#include <iostream>
using namespace std;

// Variable created inside namespace
namespace first
{
	int val = 500;
}

// Global variable
int val = 100;

int main()
{
	// Local variable
	int val = 200;

	// These variables can be accessed from
	// outside the namespace using the scope
	// operator ::
	cout << first::val << '\n';

	return 0;
}

```

Namespaces allow us to group named entities that otherwise would have global scope into narrower scopes, giving them namespace scope. This allows organizing the elements of programs into different logical scopes referred to by names.
>Using namespace, you can define the context in which names are defined.

In order to define the namespace, we have to use the prepend(::) operator.

#### The using directive
You can also avoid prepending of namespaces with the using namespace directive. This directive tells the compiler that the subsequent code is making use of names in the specified namespace. The namespace is thus implied for the following code −

```cpp
#include <iostream>
using namespace std;

// first name space
namespace first_space {
   void func() {
      cout << "Inside first_space" << endl;
   }
}

// second name space
namespace second_space {
   void func() {
      cout << "Inside second_space" << endl;
   }
}

using namespace first_space;
int main () {
   // This calls function from first name space.
   func();
   
   return 0;
}

OUTPUT:- 
Inside first_space
```

The ‘using’ directive can also be used to refer to a particular item within a namespace. For example, if the only part of the std namespace that you intend to use is cout, you can refer to it as follows −

`using std::cout;`

Another example:-
```cpp
#include <vector>
 
namespace vec {
 
    template< typename T >
    class vector {
        // ...
    };
 
} // of vec
 
int main()
{
    std::vector<int> v1; // Standard vector.
    vec::vector<int> v2; // User defined vector.
 
    v1 = v2;             // Error: v1 and v2 are different object's type.
 
    {
        using namespace std;
        vector<int> v3;  // Same as std::vector
        v1 = v3; // OK
    }
 
    {
        using vec::vector;
        vector<int> v4;  // Same as vec::vector
        v2 = v4; // OK
    }
 
    return 0;
}
```


---
### Constructors in C++
A constructor is a special type of member function of a class which initializes objects of a class. In C++, Constructor is automatically called when object(instance of class) create. It is special member function of the class because it does not have any return type.
How constructors are different from a normal member function?

A constructor is different from normal functions in following ways: 

- Constructor has same name as the class itself
- Constructors don’t have return type
- A constructor is automatically called when an object is created.
- It must be placed in public section of class.
- If we do not specify a constructor, C++ compiler generates a default constructor for object (expects no parameters and has an empty body).


>
>
Let us understand the types of constructors in C++ by taking a real-world example. Suppose you went to a shop to buy a marker. When you want to buy a marker, what are the options? The first one you go to a shop and say give me a marker. So just saying give me a marker mean that you did not set which brand name and which color, you didn’t mention anything just say you want a marker. So when we said just I want a marker so whatever the frequently sold marker is there in the market or in his shop he will simply hand over that. And this is what a default constructor is! The second method you go to a shop and say I want a marker a red in color and XYZ brand. So you are mentioning this and he will give you that marker. So in this case you have given the parameters. And this is what a parameterized constructor is! Then the third one you go to a shop and say I want a marker like this(a physical marker on your hand). So the shopkeeper will see that marker. Okay, and he will give a new marker for you. So copy of that marker. And that’s what copy constructor is!

##### Default Constructors
```cpp
// Cpp program to illustrate the
// concept of Constructors
#include <iostream>
using namespace std;

class construct
{
public:
	int a, b;

	// Default Constructor
	construct()
	{
		a = 10;
		b = 20;
	}
};

int main()
{
	// Default constructor called automatically
	// when the object is created
	construct c;
	cout << "a: " << c.a << endl
		<< "b: " << c.b;
	return 1;
}

```
##### Parameterized Constructors
```cpp
// CPP program to illustrate
// parameterized constructors
#include <iostream>
using namespace std;

class Point
{
private:
	int x, y;

public:
	// Parameterized Constructor
	Point(int x1, int y1)
	{
		x = x1;
		y = y1;
	}

	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
};

int main()
{
	// Constructor called
	Point p1(10, 15);

	// Access values assigned by constructor
	cout << "p1.x = " << p1.getX() << ", p1.y = " << p1.getY();

	return 0;
}
```

Uses of Parameterized constructor: 
- It is used to initialize the various data elements of different objects with different values when they are created.
- It is used to overload constructors.

##### Copy Constructors
```cpp
// CPP program to illustrate
// copy constructors
#include <iostream>
using namespace std;

// declare a class
class Wall {
  private:
    double length;
    double height;

  public:

    // initialize variables with parameterized constructor
    Wall(double len, double hgt) {
      length = len;
      height = hgt;
    }

    // copy constructor with a Wall object as parameter
    // copies data of the obj parameter
    Wall(Wall &obj) {
      length = obj.length;
      height = obj.height;
    }

    double calculateArea() {
      return length * height;
    }
};

int main() {
  // create an object of Wall class
  Wall wall1(10.5, 8.6);

  // copy contents of wall1 to wall2
  Wall wall2 = wall1;

  // print areas of wall1 and wall2
  cout << "Area of Wall 1: " << wall1.calculateArea() << endl;
  cout << "Area of Wall 2: " << wall2.calculateArea();

  return 0;
}
```

---
### WHAT ARE THREADS?

[click here!](https://www.backblaze.com/blog/whats-the-diff-programs-processes-and-threads/)

---
