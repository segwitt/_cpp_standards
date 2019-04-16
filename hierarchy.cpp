#include <iostream>
using std::cout ;



class A
{
public:
	A(){};
	~A(){};
	void print() {
		cout << "A\n";
	}

};

class B : public A
{
public:
	B(){};
	~B(){};
	void print() {
		A::print();
		cout << "B\n";
	}
	
};

class C : public B
{
public:
	C(){};
	~C(){};
	void print() {
		B::print();
		cout << "C\n";
	}
	
};

int main(int argc, char const *argv[])
{
	
	A* a = new A();
	B* b = new B();
	C* c = new C();
	a->print();
	cout << "\n";
	b->print();
	cout << "\n";
	c->print();


	return 0;
}