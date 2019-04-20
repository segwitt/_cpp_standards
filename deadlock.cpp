#include <iostream>
#include <thread>
#include <mutex>
using std::cout;
using std::endl;
using std::string;

class A
{

	//ofstream f
	// good to use this practice of bundling a sharable resource with mutex so that it is accessed only when locked
	std::mutex _m1;
	std::mutex _m2;

public:
	A() {} ;

	void print1(string id, int value) {

		std::lock_guard<std::mutex> locker1(_m1);
		std::lock_guard<std::mutex> locker2(_m2);
		cout << "thread  id " << id << " value " << value << endl;
	}
	void print2(string id, int value) {

		std::lock_guard<std::mutex> locker2(_m2);
		std::lock_guard<std::mutex> locker1(_m1);
		// f << 
		cout << "thread  id " << id << " value " << value << endl;

	}

	// ofstream getF(); // bad idea, access with muteex

	~A() {} ;
	
};

void function1(A& a) { for(int i = 200; i < 301; ++i) a.print1("thread1", i); }

int main(int argc, char const *argv[])
{
	
	A a;
	std::thread thread1(function1, std::ref(a) );
	for (int i = 0; i < 100; ++i)
	{
		// accessing a resource wrapped along with mutex , good practice
		a.print2(string("main "), i);
	}
	thread1.join();

	return 0;
}

// to compile ,    g++ -pthread -o main deadlock.cpp

/*

A parameter to a thread is always passed by value
to pass by ref we use std::ref() which creates a reference wrapper
or we can move the value using std::move() (a thread can be only moved)


mutex used for synchronisation

each thread has identification number associated with it

we can use mutex.lock() and mutex.unloK() but it is not exception safe
we use lock guard so when ever it goes out of scope , whether exception or not , it is freed

thread safey - a program is thread safe which processes data independently and wholly for different threads
independent of context switches

*/