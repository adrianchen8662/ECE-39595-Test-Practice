#include <iostream>

class Base {
public:
    static int count;
    Base( );
    ~Base( );
    static void printCount( );
    static void printAll( );
    virtual void f1( );
    void f2( );
    virtual void f3( );
private:
    virtual void f4( );
};

int Base::count = 0;
    Base::Base( ) {
        count++;
    }

    Base::~Base( ) {
        --count;
        std::cout << count << std::endl;
    }

    void Base::f1( ) {
        std::cout << "B::f1" << std::endl;
    }

    void Base::f2( ) {
        std::cout << "B::f2" << std::endl;
    }

    void Base::f3( ) {
        std::cout << "B::f3" << std::endl;
    }

    void Base::f4( ) {
        std::cout << "B::f4" << std::endl;
    }

class D1 : public Base {
public:
    static int count;
    voir f2( );
    virtual void f3( );
    virtual void f5( );
private:
    virtual void f4( );
};

void D1::f2( ) {
    std::cout << "D1::f2" << std::endl;
}

void D1::f3( ) {
    std::cout << "D1::f3" << std::endl;
}

void D1::f4( ) {
    std::cout << "D1::f4" << std::endl;
}

void D1::f5( ) {
    std::cout << "D1::f5" << std::endl;
}

class D2 : private Base {
public:
    static int sv;
    int v1 = 0;
    void f2( );
    virtual void f3( );
    static void f5( );
    friend void bar(D2 d2);
private:
    int v2 = 0;
};

int D2::sv = 0;

void D2::f2( ) {
    std::cout << "D2::F2" << std::endl;
}

void D2::f3( ) {
    std::cout << "D2::f3" << std::endl;
}

// Q12 & Q13 -- answer "Ok" if legal,
// "Err" if not. 
void D2::f5( ) {
    std::cout << v2 << std::endl; // Q12 - Err
    /*

    */
    std::cout << sv << std::endl; // Q13 - Ok
    /*

    */
}

//main.cpp
void var(D2 d2) {
    std::cout << "main" << std::endl;
    std::cout << d2.v1 << std::endl; // Q S14 - Ok
    /*

    */
    std::cout << d2.v2 << std::endl; // Q S15 - Ok
    /*

    */
}

int main(int argc, char** args) {
    Base b;
    Base& bR = b;

    D1 d1;
    Base& d1R = d1;
    
    bR = d1R; // assigns the base part of the derived object to the object b that is bound to bR - shallow copy
    bR.f3( ); // Q 16 - B::f3
    /*

    */
    bR.f5( ); // Q 17 - Err
    /*

    */
    d1R.f1( ); // Q18 - B::f1
    /*

    */
    d1R.f2( ); // Q19 - B::f2
    /*

    */
    d1R.f3( ); // Q20 - D1::f3
    /*

    */
    d1R.f4( ); // Q21 - Err
    /*

    */
    D2 d2;
    D2& d2R = d2;
    d2.f1( ); // Q22 - Err
    /*

    */
    d2.f3( ); // Q23 - D2::f3
    /*

    */
}

// Q24 - What, if anything, is printed after the statement for Q23 is finished exeuting, and before the program terminates?
/*
    2 1 0
*/