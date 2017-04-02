#include <iostream>
#include "TypeInfo.h"

struct Base
{
    int k;
};

struct DerivedA : Base
{
    char c;
};

struct DerivedB : Base
{
    int a;
    int b;
};


struct Derived : DerivedA, DerivedB
{
    int a;
    int b;
};

int main() {
    Base *a = NEW(DerivedA, a);
    Base *b = NEW(Base, b);
    std::cout << TYPEID(a).name << "\n";
    std::cout << TYPEID(b).name << "\n";
    std::cout << "Base size = " << sizeof(Base) << " derivedA size = " << sizeof(DerivedA) << "\n";
    std::cout << "DerivedB size = " << sizeof(DerivedB) << " derived size = " << sizeof(Derived) << "\n";

    return 0;
}