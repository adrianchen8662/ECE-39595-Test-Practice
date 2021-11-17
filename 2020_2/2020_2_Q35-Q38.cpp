#include <iostream>

class Base {
    virtual void h( );
};

void Base::h( ) {
    std::cout << "h" << std::endl;
}

class X : public Base {
public:
    virtual void f( );
};

void X::f( ) {
    std::cout << "f" << std::endl;
}

class Y : public Base {
public:
    virtual void g( );
};

void Y::g( ) {
    std::cout << "g" << std::endl;
}

int main(int argc, char** args) {
    Base* b = new Base( );
    X* x = new X( );
    Y* y = new Y( );

    y = new Y( );
    y = static_cast<Y*>(b); // S1

    y = new Y( );
    y = static_cast<Y*>(x); // S2

    y = new Y( );
    y = dynamic_cast<Y*>(b); // S3
    y->g( ); // S4
}

// Q35 - Does S1 give an error at compile time? 
/*
    No
*/

// Q36 - Does S2 give an error at compile time?
/*
    Yes
    Wrong inherit
*/

// Q37 - Does S3 give an error at compile time?
/*
    No
*/

// Q38 - Does S4 give an error at run time?
/*
    Yes
    The cast goes as b is cast into Y. B doesn't have a g() function. 
*/