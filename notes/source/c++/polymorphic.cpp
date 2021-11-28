#include <iostream>
using namespace std;

struct A {
    void f() { cout << "A::f" << endl; }
    virtual void g() { cout << "A::g" << endl; }
};

struct B : public A {
    void f() { cout << "B::f" << endl; }
    void g() override { cout << "B::g" << endl; }
};

int main() {
    A a;
    B b;
    A ab = B();
    a.f(); a.g();
    b.f(); b.g();
    ab.f(); ab.g();

    cout << "------------" << endl;

    A* pa = &a;
    B* pb = &b;
    A* pab = &b;
    pa->f(); pa->g();
    pb->f(); pb->g();
    pab->f(); pab->g();

    cout << "------------" << endl;

    A& ra = a;
    B& rb = b;
    A& rab = b;
    ra.f(); ra.g();
    rb.f(); rb.g();
    rab.f(); rab.g();
}
