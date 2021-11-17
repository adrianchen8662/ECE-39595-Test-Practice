#include <iostream>

class Base {
public:
int val;
Base(int _val);
virtual void foo( );
};

Base::Base(int _val) : val(_val) { }

void Base::foo( ) {
    std::cout << "B::foo" << std::endl;
}

class D1 : virtual public Base {

public:
    D1(int val);
};

D1::D1(int val) : Base(-val) { }

class D2 : virtual public Base {
public:
    D2(int val);
};

D2::D2(int val) : Base(-val) { }

class Derived : public D1, public D2 {
public:
    Derived(int val);
};

Derived::Derived(int val) : Base(val), D1(val), D2(val) { }

int main(int argc, char** args) {
    Base b(0);
    D1 d1(10);
    D2 d2(20);
    Derived d(30);
    std::cout << b.val << std::endl; // Q11 - 0
    /*
        Assigned at 39
    */
    std::cout << d1.val << std::endl; // Q12 - -10
    /*
        d1 constructor negs value
    */
    std::cout << d.D2::val << std::endl; // Q13 - 30
    /*
        Assigned at 42
    */
}