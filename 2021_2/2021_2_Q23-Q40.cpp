#include <iostream>

// B1.h
class B1 {
private:
    virtual void f1( );
public:
    int v;
    B1(int i);
    virtual ~B1( );
    virtual void f2(B1* p);
    virtual void f3( )=0;
    void f4( );
};

// B1.cpp
B1::B1(int i) : v(i) {
    std::cout << "B1 c";
}

B1::~B1( ) {
    std::cout << "B1 d";
}

void B1::f1( ) {
    std::cout << "B1::f1" << std::endl;
}

void B1::f2(B1* b) {
    std::cout << "B1::f2" << std::endl;
}

void B1::f4( ) {
    std::cout << "B1::f4" << std::endl;
}

// B2.h
class B2 {
private:
    virtual void f1( );
public:
    int v;
    B2(int i);
    virtual ~B2( );
    virtual void f2(B2* p);
    virtual void f3( );
    void f4( );
};

// B2.cpp
B2::B2(int i) : v(i) {
    std::cout << "B2 c";
}

B2::~B2( ) {
    std::cout << "B2 d";
}

void B2::f1( ) {
    std::cout << "B2::f1" << std::endl;
}

void B2::f2(B2* p) {
    std::cout << "B2::f2" << std::endl;
p->f1( );
}

void B2::f3( ) {
    std::cout << "B2::f3" << std::endl;
}

void B2::f4( ) {
    std::cout << "B2::f4" << std::endl;
}

// D.h
class D : public B2 {
private:
    virtual void f1( );
public:
    int v;
    D(int i);
    D(D& d);
    virtual ~D( );
    void f2(B2* p);
    void f3( );
    void f4( );
    virtual void f5( );
};

// D.cpp
D::D(int i) : B2(5), v(i) {
    std::cout << "D c" << std::endl;
}

D::D(D& d) : B2(d.v), v(100) {
    std::cout << "D cc" << std::endl;
}

D::~D( ) {
    std::cout << "D d" << std::endl;
}

void D::f1( ) {
    std::cout << "D::f1" << std::endl;
}

void D::f2(B2* p) {
    std::cout << "D::f2" << std::endl;
    ((D*) p)->f1( );
}

void D::f3( ) {
    std::cout << "D::f3" << std::endl;
}

void D::f4( ) {
    std::cout << "D::f4" << std::endl;
}

void D::f5( ) {
    std::cout << "D::f5" << std::endl;
}

void foo(D d) {
    std::cout << d.v << std::endl;
}

void f1(D& d) {
    std::cout << d.v << std::endl;
}

void f1(D* d) {
    std::cout << d->v << std::endl;
    d = nullptr;
}

int main(int argc, char** args) {
    B1* b1P = new B1(2); // Q23 - Err
    /*
        
    */
    B2* b2P = new D(2); // Q24 - B2 cD c
    /*
        D inherits from B2, so when declaring a B2 type D, it works
        Prints from the constructor at B::~B2, then prints from the constructor at D::D
        Because it first constructs as B2, then D, B2's functions are added first then D's to overload
    */
    D* dP = (D*) b2P;
    
    b2P->f1( ); // Q25 - Err
    /*
        f1 is declared as private only to b2P, and since b2P was declared as a D, it doesn't have access
    */
    b2P->f2(b2P); // Q26 - D::f2 D::f1
    /*
        f2 would first execute D's function, then pass to f1. This is ok because 
    */
    b2P->f3( ); // Q27 - D::f3
    /*
        f3 is D's own function, and overrides b2P's f3 function
    */
    b2P->f4( ); // Q28 - B2::f4
    /*
        f4 in B2 was declared as a void, not a virtual void, overriding D's own f4
    */
    b2P->f5( ); // Q29 - Err    
    /*
        B2 was constructed first, then D. D's f5 was a virtual function, so it doesn't construct and doesn't exist
    */
    std::cout << b2P->v << std::endl; // Q30 - 5
    /*
        in the constructor for D, B2 was passed in the initializer list as B2(5), assigning 5 to v
    */
    dP->f3( ); // Q31 - D::f3
    /*

    */
    dP->f4( ); // Q32 - D::f4
    /*

    */
    std::cout << dP->v << std::endl; // Q33 - 2
    /*

    */
    B2 b(1);
    D d(2);
    foo(d); // Q34 - B2 cD cc D d B2 d or Err
    /*

    */
    f1(d); // Q35 - 2 or Err
    /*

    */
    dP = new D(10);
    f1(dP); // Q36 - 10 or Err
    /*

    */
    if (dP==nullptr) { // Q37 - not null
        /*

        */
        std::cout << "null" << std::endl;
    } else {
        std::cout << "not null" << std::endl;
    }

    b = d; // Q38 - Ok
    /*

    */
    b.f2(&b); // Q39 - B2::f2 B2::f1
    /*

    */
    std::cout << b.v << std::endl;

} // Q40 What, if anything, is printed
// as the program exits? - D d B2 d B2 d
/*

*/