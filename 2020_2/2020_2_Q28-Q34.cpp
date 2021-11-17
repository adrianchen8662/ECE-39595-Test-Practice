#include <iostream>

class Base {
public:
    static int count;
    Base( );
    virtual void h(double);
    virtual void h(int);
    virtual void h( );
};

int Base::Base::count = 0;
Base::Base( ) {
    count++;
}

void Base::h(double d) {
    std::cout << "B::hd" << std::endl;
}

void Base::h(int i) {
    std::cout << "B::hi" << std::endl;
}

void Base::h( ) {
    std::cout << "B::hv" << std::endl;
}

class D1 : public Base {
public:
    virtual void h(int);
};

void D1::h(int i) {
    std::cout << "D1::hi" << std::endl;
}

class D2 : public Base {
public:
    virtual void h(int);
    using Base::h;
};

void D2::h(int) {
    std::cout << "D2::hi" << std::endl;
}

int main(int argc, char** args) {

    D1* d1 = new D1( ); // 28 - Ok
    /*
        Not pvf
    */
    d1->h(2.0); // 29 - D1::hi
    /*
        Goes to D1::h
    */
    d1->h( ); // 30 - Err
    /*
        D1 has no h that is empty
    */
    D2* d2 = new D2( ); // 31 - Ok
    /*
        Not pvf
    */
    d2->h(1); // 32 - D2::hi
    /*
        Has its own D2::h(int)
    */
    d2->h( ); // 33 - B::hv
    /*
        has using "Base::h" so it uses that
    */
    Base b;

    std::cout << b.count << std::endl; // 34 - 3
    /*
        b constructor called 3 times: line 50, line 62, line 74
    */
}