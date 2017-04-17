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
    int d = 20;
    int e = 100;
    int c = 10;
};

struct EXTENDS(DerivedB, Base)
    int e = 115;
    int a;
    int b;
};


struct MEXTENDS(Derived, DerivedA, DerivedB)
    int a;
    int b;
};

int main() {
    Base *a = NEW(Base, DerivedB, a);
    Base *b = NEW(Base, Base, b);
    DerivedB *d = NEW(DerivedB, Derived, d);
    for( int i = -100; i < 100; ++i) {
        if (reinterpret_cast<DerivedA *>((char *) (d) + i)->c == 10) {
            std::cout << i << " " << reinterpret_cast<DerivedA *>((char *) (d) + i)->c << "\n";
        }
    }
   // std::cout << DYNAMIC_CAST(DerivedB, DerivedA, d)->c << "\n";
    std::cout << DYNAMIC_CAST(Derived, DerivedA, d)->c << "\n";
    std::cout << TYPEID(d).name << "\n";
    std::cout << TYPEID(a).name << "\n";
    std::cout << TYPEID(b).name << "\n";
    std::cout << "Base size = " << sizeof(Base) << " derivedA size = " << sizeof(DerivedA) << "\n";
    std::cout << "DerivedB size = " << sizeof(DerivedB) << " derived size = " << sizeof(Derived) << "\n";
    std::cout << graph["DerivedB"]["Base"] << "\n";
    for( auto i = graph["Derived"].begin(); i != graph["Derived"].end(); ++i ){
        std::cout << i->first << " " << i->second << "\n";
    }
    return 0;
}