#include <iostream>
using namespace std;

class A {
  public:
    A()  { cout << __func__ << endl; }
    ~A() { cout << __func__ << endl; }
};

class B : public A {
  public:
    B() { cout << __func__ << endl; }
    ~B() { cout << __func__ << endl; }
};

class C : public B {
  public:
    C() { cout << __func__ << endl; }
    ~C() { cout << __func__ << endl; }
};

class D : public C {
  public:
    D() { cout << __func__ << endl; }
    ~D() { cout << __func__ << endl; }
};

int main() {
    cout << "test konstruktorjev in destruktorjev:" << endl;
    { D d; }
    return 0;
}
