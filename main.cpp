#include <iostream>
#include "TypeInfo.h"
#include <typeinfo>
struct Base
{
    virtual void f(){}
    int k;
};

struct EXTENDS(DerivedA, Base)
    virtual void f(){}
    int c = 10;
};

struct EXTENDS(DerivedB, Base)
    int a;
    int b;
};


struct MEXTENDS(Derived, DerivedA, DerivedB)
    int a;
    int b;
};

int main() {
    Base *a = NEW(DerivedA, a);
    Base *b = NEW(Base, b);
    DerivedA *d = NEW(Derived, d);
    for( int i = -100; i < 100; ++i) {
        if (reinterpret_cast<Derived *>(d + i)->c == 10) {
            std::cout << i << " " << reinterpret_cast<Derived *>(d + i)->c << "\n";
        }
    }
    std::cout << reinterpret_cast<Derived *>(d)->c << "\n";
    std::cout << TYPEID(d).name;
    std::cout << DYNAMIC_CAST(Derived, d)->c << "\n";
    std::cout << TYPEID(a).name << "\n";
    std::cout << TYPEID(b).name << "\n";
    std::cout << "Base size = " << sizeof(Base) << " derivedA size = " << sizeof(DerivedA) << "\n";
    std::cout << "DerivedB size = " << sizeof(DerivedB) << " derived size = " << sizeof(Derived) << "\n";
    std::cout << reinterpret_cast<DerivedA*>(a)->c << "\n";
    for( auto i = graph["Derived"].begin(); i != graph["Derived"].end(); ++i ){
        std::cout << *i << "\n";
    }
    return 0;
}