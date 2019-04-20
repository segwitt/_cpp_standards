#include <iostream>
#include <thread>
#include <mutex>
using std::cout;
using std::endl;
using std::string;

class A
{
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
		cout << "thread  id " << id << " value " << value << endl;

	}
	~A() {} ;
	
};

void function1(A& a) { for(int i = 200; i < 301; ++i) a.print1("thread1", i); }

int main(int argc, char const *argv[])
{
	
	A a;
	std::thread thread1(function1, std::ref(a) );
	for (int i = 0; i < 100; ++i)
	{
		a.print2(string("main "), i);
	}
	thread1.join();

	return 0;
}

// g++ -pthread -o main deadlock.cpp