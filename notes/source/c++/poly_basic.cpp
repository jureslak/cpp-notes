#include <iostream>
using namespace std;

struct Animal {
    string oglasanje() const { return "";}
};

struct Dog : public Animal {
    string oglasanje() const { return "Hov"; }
};

int main() {
    Animal* a = new Dog();
    cout << a->oglasanje() << endl;
    return 0;
}
