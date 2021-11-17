#include <iostream>

class Base {
public:
    static void fstat( );
    virtual void f1( );
    void f3( );
    virtual void f4( );
private:
    virtual void f5( );
};

void Base::fstat( ) {
    std::cout << "B::fs" << std::endl;
}

void Base::f1( ) {
    std::cout << "B::f1" << std::endl;
}

void Base::f3( ) {
    std::cout << "B::f3" << std::endl;
}

void Base::f4( ) {
    std::cout << "B::f4 ";
    f5( );
}

void Base::f5( ) {
    std::cout << "B::f5" << std::endl;
}

class Derived : public Base {
public:
    static void fstat( );
    virtual void f1( );
    virtual void f2( );
    void f3( );
private:
    virtual void f5( );
};

void Derived::fstat( ) {
    std::cout << "D::fs" << std::endl;
}

void Derived::f1( ) {
    std::cout << "D::f1" << std::endl;
}

void Derived::f2( ) {
    std::cout << "D::f2" << std::endl;
}
void Derived::f3( ) {
    std::cout << "D::f3" << std::endl;
}

void Derived::f5( ) {
    std::cout << "D::f5" << std::endl;
}

// Main.cpp code
void f(int* ip) {
    *ip = 2;
    ip = nullptr;
}

void f(Derived& d) {
    std::cout << "D&&" << std::endl;
}

void f(Derived&& d) {
    std::cout << "D&&" << std::endl;
}

int main(int argc, char** args) {
    Base* b = new Base( );
    Base* bd = new Derived( );

    b->f4( ); // Q30 - B::f4, B::f5
    /*
        b is a base class, so when f4 is called it goes to f4, then f5
    */
    bd->fstat( ); // Q31 - B::fs
    /*
        bd inherits fstat from B because public and not virtual
    */
    bd->f1( ); // Q32 - D::f1
    /*
        bd has its own f1
    */
    bd->f2( ); // Q33 - Err
    /*
        B doesn't have a f2
    */
    bd->f3( ); // Q34 - B::f3
    /*
        bd has its own f3, which is overriden because not virtual
    */
    f(Derived( )); // Q35 - D&&
    /*
        It's a derived class, no problems
    */
    Derived d;
    f(d); // Q36 - D&&
    /*
        Derived is also a derived class, no problems
    */
    int i = 4; // S1
    int* ip = &i;
    f(ip);
    std::cout << i << std::endl; // Q37 - 2
    /*
        gets ip value
    */
    std::cout << ip << std::endl; // S2
}

//Q38 - In statement S1, which is correct
// B. 4 is an rvalue and i is the lvalue
/*
    B
*/

//Q39 - Is ip == nullptr in S2? Answer true or false
/*
    false
*/