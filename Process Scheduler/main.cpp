#include <iostream>
using namespace std;
class A {
public:
	virtual void fun() {
		cout << "Hello ";
	}
};
class B : A {
public:
	void fun() override {
		A::fun();
		cout << "World";
	}
};
int main() {
	B* b = new B();
	b->fun();
}