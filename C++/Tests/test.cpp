// author: Adrian Michałek
// email: devmichalek@gmail.com

// 0.1 How the console would look like after executing this code?
#include <stdio.h>

int do_a() { printf("A"); return 0; }
char do_b() { printf("B"); return 0; }

class A
{
	int a = do_a();
public:
	A(int a = 0) { printf("C"); };
private:
	char b = do_b();
};

void do_d(int x, int y, A z) {
	printf("D");
}

int main()
{
	do_d(do_a(), do_b(), A());
	return 0;
}

// 0.2 Write class C with the solution for constructors having the same basic code without duplicating.
//	   Explain why class B has the wrong approach.
class A
{	// wrong approach
	void init() {}
public:
	A() { init(); }
	A(int x) { init(); }
};

class B
{	// wrong approach
public:
	B() { /*init*/ }
	B(int x) { B(); }
};

// 0.3 Following code gives an error: "no appropriate default constructor available".
// 	   Force compiler to generate default constructor for class Dog (use C++11 feature).
class Dog
{
	int age;
public:
	Dog(int age) { this->age = age; }
	/* implementation goes here */

	/* implementation ends here*/
};

int main()
{
	Dog dog;
	return 0;
}

// 0.4 Write lambda function that takes one integer parameter and checks if integer is greater than 3.
#include <iostream>
#include <vector>

template<typename func>
void filter(func f, std::vector<int> arr) {
	for (auto i : arr) {
		if (f(i))
			std::cout << i << " ";
	}
}

int main()
{
	std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
	filter(/*implementation*/, v);
	return 0;
}

// 0.5 Finish following lamba functions.
#include <stdio.h>

int main()
{
	int a = 0, b = 1, c = 2, d = 3;
	auto f1 = [/*pass variable a by reference*/]() { a = 1; printf("%d\n", a); };
	auto f2 = [/*pass all variables by const copy*/]() { printf("%d\n", a + b + c + d); };
	auto f3 = [/*pass all variables by reference except variable b*/]() { a = c = d; printf("%d\n", b); };
	return 0;
}

// 0.6 Where is the bug in the following code?
#include <iostream>

class MyVector {
	int size;
	double* arr;
public:
	MyVector(int &&newSize) {
		size = newSize;
		arr = new double[size];
		for (int i = 0; i < size; ++i)
			arr[i] = i;
	}

	MyVector(const MyVector &rhs) {
		size = rhs.size;
		arr = new double[size];
		for (int i = 0; i < size; ++i) {
			arr[i] = rhs.arr[i];
		}
	}

	MyVector(MyVector &&rhs) {
		size = rhs.size;
		arr = rhs.arr;
	}

	~MyVector() {
		if (arr) {
			delete[] arr;
			arr = nullptr;
		}

		size = 0;
	}

	double getFirst() { return arr ? arr[0] : -1; }
};

MyVector getMyVector() {
	MyVector buffer(10);
	return buffer;
}

int main()
{
	MyVector v1(10);
	MyVector v2(v1);
	MyVector v3(getMyVector());
	std::cout << v1.getFirst() << " " << v2.getFirst() << " " << v3.getFirst();
	return 0;
}

// 0.7 Why this piece of code is not safe?
//	   What should be improved?
#include <memory>

struct Dog {};

int main()
{
	std::shared_ptr<Dog> p1 = std::make_shared<Dog>();
	std::shared_ptr<Dog> p2 = std::shared_ptr<Dog>(new Dog());
	std::shared_ptr<Dog> p3(new Dog[3]);
	std::shared_ptr<Dog> p4 = nullptr;
	return 0;
}

// 1.0 What is the output for the following code?
#include <iostream>
#include <string>

struct Dog {
	void bark(int age) { std::cout << "I am " << age << " years old." << std::endl; }
	virtual void bark(std::string msg = "just a") { std::cout << "I am " << msg << " dog" << std::endl; }
};

struct YellowDog : public Dog {
	virtual void bark(std::string msg = "Yellowdog") { std::cout << "I am " << msg << " dog" << std::endl; }
};

int main()
{
	YellowDog* yd = new YellowDog;
	yd->bark();
	yd->bark(2);
	delete yd;
	return 0;
}

// 1.1 What is the output for the following code?
#include <iostream>

void func(int* x)
{
	*x = 7;
}

int main()
{
	const int a = 3;
	int* ptr;
	ptr = const_cast<int*>(&a);
	std::cout << "A=" << a << std::endl;
	*ptr = 5;
	std::cout << "A=" << a << std::endl;
	*((int*)(&a)) = 6;
	std::cout << "A=" << a << std::endl;
	func((int*)(&a));
	std::cout << "A=" << a << std::endl;
	return 0;
}

// 1.2 Add comments next to p1, p2, p3 and p4, what is const in each line?
//	   Describe "const" with pointers and objects.
int main()
{
	int i;
	const int* p1 = &i;			// comment here
	p1++;
	int* const p2 = &i;			// comment here
	const int* const p3 = &i;	// comment here
	int const* p4 = &i;			// comment here
}

// 1.3 What is the output (and why) of the following code?
#include <iostream>

int main()
{
	int i = 2;
	const int& ref = i;
	const int* ptr = &i;

	i = 2;
	const_cast<int&>(ref) = 3;
	*const_cast<int*>(ptr) = 4;

	std::cout << i << ' ' << ref << ' ' << *ptr;
}

// 1.4 The code below wouldn't compile. Give at least two correct implementations.
// 	   What is the output (and why) of the following code?
//	   You can add or delete only one word in each solution.
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class Dog
{
	string name;
public:
	Dog() { name = "dummy"; printDogName(); }
	const string& getName() { return name; }

	void printDogName() const { cout << getName() << " const" << endl; }
	void printDogName() { cout << getName() << " not const" << endl; }
};

int main()
{
	Dog d1;
	const Dog d2;
	d1.printDogName();
	d2.printDogName();
	return 0;
}

// 1.5 Describe the function below:
	const int* const fun(const int* const& p) const;

// 1.6 Edit the class so that getItem is a const function that returns v[index]
// 	   and increments the accessCounter.
//	   The following code wouldn't compile, repair it. Give two solutions.
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class BigArray
{
	vector<int> v;
	int accessCounter;

public:
	int getItem(int index) const
	{
		accessCounter++;
		return v[index];
	}
};

// 1.7 Predict the output of console for:
#include <stdio.h>
void fun(char **p)
{
	char* t;
	t = (p += sizeof(int))[-1];
	printf("%s\n", t);
}

int main()
{
	const char* argv[] = { "ab", "cd", "ef", "gh", "ij", "kl" };
	fun((char**)argv);
	return 0;
}

// 1.8 What is the output for the following code?
#include <stdio.h>
int main()
{
	int a[][3] = { 1, 2, 3, 4, 5, 6 };
	int(*ptr)[3] = a;
	printf("%d %d ", (*ptr)[1], (*ptr)[2]);
	++ptr;
	printf("%d %d\n", (*ptr)[1], (*ptr)[2]);
	return 0;
}


// 2.1 Disallow copy constructor in the following code.
// 	   Give at least two solutions. Do not change/add other behaviours.
#include <string>
#include <iostream>

struct Human
{
	Human(std::string name) { std::cout << "My name is " << name << std::endl; }
};

int main(int argc, char **argv)
{
	Human h1(std::string("John"));
	Human h2(h1); // copy constructor shouldn't compile
	return 0;
}


// 2.2 Keep ~Human() private add mechanism of freeing memory at the same time
// 	   in the following code. Do not change/add other behaviours.
#include <string>
#include <iostream>

class Human
{
	~Human() { std::cout << "Goodbye" << std::endl; }
public:
	Human(std::string name) { std::cout << "My name is " << name << std::endl; }
};

int main(int argc, char **argv)
{
	Human* of = new Human("name");
	return 0;
}

// 2.3 What is the output of the following code?
#include <string>
#include <iostream>

struct Cat
{
	Cat() { std::cout << "A"; }
	Cat(std::string str) { std::cout << str; }
};

struct Dog
{
	Dog(std::string str) { std::cout << str; }
};

int main(int argc, char **argv)
{
	Cat c1("B");
	Dog d1;
	Cat c2("A");
	Cat c3;
	Dog d2("C");
	return 0;
}

// 2.4 Change the DogFactory's function createYellowDog() so that there is no
// 	   need to use virtual keyword in parent class.
//	   Hint: use shared_ptr.
#include <memory>
struct Dog
{
	/*virtual*/ ~Dog() {}
};

struct Yellowdog : public Dog
{
	~Yellowdog() {}
};

struct DogFactory
{
	//static Dog* createYellowDog() { return new Yellowdog(); }
};

// 2.5 What is the difference between malloc(), calloc() and realloc()?

// 2.6 Implement safe self assignment operator. Give two solutions.
//	   Do deleting c(Collar) before creating new Collar is safe?
class Collar;
class Dog {
	Collar* c;
	Dog& operator=(const Dog &rhs) {
		// wouldn't work when
		// Dog a;
		// a = a;

		delete c;
		c = new Collar(*rhs.c);
		return *this;
	}
}

// 2.7 What is the output of the following program?
#include <stdio.h>
#define R 10
#define C 20

int main()
{
	int* p[R][C];
	printf("%d", sizeof(*p));
	return 0;
}

// 2.8 What is the output of the following executed code?
#include <stdio.h>
struct Block {
	int a[3] = { 1, 2, 3 };
	int b[3] = { 4, 5, 6 };
	unsigned char ch[4] = {0, 1, 0, 0};
	int c[3] = { 7, 8, 9 };
};

int main()
{
	Block block;
	int* ptr = (int*)(&block.b + 1);
	printf("%d %d %d", *(block.b + 1), *(ptr - 1), *ptr);
	return 0;
}

// 2.9 What # prefix does in the following code?
// 	   What is the output for the following program?
#include <iostream>
#define watch(x) std::cout << #x << " is " << x << "\n";

int main()
{
	int i = 0xFF;
	int* j = &i;
	watch(i);
	watch(*j);
	return 0;
}

// 3.0 What does the explicit keyword mean?

// 3.1 Repair the code so that the code compiles without errors.
class InputFile {
public:
	void read() {}
private:
	void open() {}
};

class OutputFile {
public:
	void read() {}
	void open() {}
};

class IOFile : public InputFile, OutputFile {};

int main()
{
	IOFile f;
	f.open();
	return 0;
}

// 3.2 What is the output for the following code?
#include <iostream>
namespace A
{
	struct X {};
	void g(X x) { std::cout << "calling A::g()\n"; }
}

struct B
{
	void g(A::X x) { std::cout << "calling B::g()\n"; }
};

class C : public B {
public:
	void j() {
		A::X x;
		g(x);
	}
};

int main()
{
	A::X x;
	g(x);
	C c;
	c.j();
	return 0;
}

// 3.3 What is the difference between function e() and f()?
int e() { return 0; }
constexpr int f() { return 0; }

int main()
{
	int a = e();
	const int b = f();
	return 0;
}

// 3.4 What does the keyword volatile amplify?
//	   What is the output of the following code?
#include <stdio.h>

int main(void)
{
	const volatile int local = 10;
	int* ptr = (int*)&local;

	printf("%d\n", local);

	*ptr = 100;

	printf("%d\n", local);
	return 0;
}

// 3.5 Disallow passing float as a parameter to constructor.
//	   Disallow copying with = operator (use C++11 feature in both).
//	   The following code should generate compile error.
class Animal
{
	int age;
public:
	Animal(int newAge) { age = newAge; }
	/* implementation starts here */


	/* implementation ends here*/
};

int main()
{
	Animal a(3);
	Animal b(3.53f); // wrong age cannot be of type float
	int number = 3;
	a = number; // wrong Animal is not a number
	return 0;
}

// 3.6 The following code would not compile, repair the code.
//	   Do the optimization and move code from C++11 to  C++14 standard.
//	   What is the output for the repaired and optimized code?
#include <iostream>

int main()
{
	int lp = 0;
	auto raport = [lp](const char* msg)
	{
		std::cout << msg << ++lp << " ";
	};

	raport("A ");
	raport("B ");
	return 0;
}

// 3.7 Define literal operator which converts binary string into integer and returns it.
#include <iostream>

/* implementation starts here */

/* implementation ends here */

int main()
{
	std::cout << "110"_strBin2Dec;
	return 0;
}