// Base.h
class Base {
public:
    virtual void ping( );
};

// Base.cpp
void Base::ping( ) { }

#include "Base.h"

// D1.h // no cpp needed since
// no new functions declared
class D1 : public Base { };

// D2.h // no cpp needed since
// no new functions declared
class D2 : public Base { };

// main.cpp
int main(int argc, char** args) {
    Base* bP = new Base( );
    D1* d1P;
    D2* d2P = new D2( );

    d1P = dynamic_cast<D1*>(d2P);
    std::cout << ((d1P == nullptr) ?
        "null" : "notnull") << std::endl; // Q10 - null
        /*
            d1P was initialized with an empty pointer, so it ends up as null
        */
    d1P = static_cast<D1*>(d2P); // Q11 - Err
    /*
        This is an error because d1P doesn't inherit from D2, it inherits from base
    */   
    d2P = static_cast<D2*>(bP); // Q12 - Ok
    /*
        This is op because d2P inherits from bP
    */
    bP = new D2( );
    d2P = static_cast<D2*>(bP);
    
    std::shared_ptr<D1> sp1 =
        std::make_shared<D1>(D1( )); // S1
    
    std::shared_ptr<D1> sp2 = sp1;
    
    std::cout << sp1.use_count( ) << std::endl; // Q13 - 2
    /*
        
    */
    // reset makes the shared pointer no longer point
    // to an object
    sp1.reset( );
    sp2.reset( ); // S2
    
    std::unique_ptr<D1> up1 =
        std::make_unique<D1>(D1( ));
    
    std::unique_ptr<D1> up2 = std::move(up1); // S3
    std::cout << sp1.use_count( ) << std::endl; // Q14 - 0
    /*

    */
}

// Q15 - move is used instead of simply assigning in S3 because
/*
    d
    It is illegal to assign a unique pointer because only one unique pointer can point to an object at a time
    Move allows only one unique_ptr to point to an object at the same time
*/

// Q16 - After the reset at S2 and the reset immediately before S2 execute, the D1 object created at S1 is freed. Answer true or false?
/*
    true

*/