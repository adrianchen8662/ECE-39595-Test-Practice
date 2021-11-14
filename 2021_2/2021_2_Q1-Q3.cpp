#include <ostream>
#include <iostream>

class GetMember {
    private:
        int f1;
        int* f2;
    public:
        GetMember(int, int*);
        int& accessInt( );
        int*& accessIntPtr( );
        friend std::ostream& operator<<(std::ostream&, const GetMember&);
};

// GetMember.cpp
GetMember::GetMember(int i, int* ip) : f1(i), f2(ip) { }

int& GetMember::accessInt( ) {
    return f1;
}

int*& GetMember::accessIntPtr( ) {
    return f2;
}

std::ostream& operator<<(std::ostream& os, const GetMember& obj) {
    os << "f1: " << obj.f1 << " ";
    if (obj.f2 == nullptr) {
        os << "f2: null ";
    } else {
        os << "f2: " << *obj.f2 << " ";
    }
    return os;
}
// main.cpp
    int main(int argc, char** args) {
    // creates an int on the heap with a value of 2
    int* ip = new int(2);
    GetMember gm(1, ip);
    
    int i = gm.accessInt( );
    gm.accessInt( ) = 20; // Q1
    /*
        This is OK because gm.accessInt() returns the address of the int, so you can just set the value to 20
    */

    int* ip2 = gm.accessIntPtr( );
    gm.accessIntPtr( ) = nullptr;

    std::cout << gm << "i: " << i << " ip: " << *ip2 << std::endl; // Q2 - f1: 20 f2: null i: 1 ip: 2
    /*
        gm gives the ostream operator overload, printing the values of f1 and f2. 
        f1 = 20
        f2 = null
        f1 is 20 from line 42, and f2 is null from line 48

        i is 1 from line 41. Line 42 never actually changes the value stored at the local variables in main
        ip is 2 from line 38/39. Line 48 never actually changes the value at the local variables in main
    */
    
    gm.accessIntPtr( ) = ip;
    std::cout << gm << std::endl; // Q3 - f1: 20 f2: 2
    /*
        f2 is now changed to 2 instead of null because the value is changed from 61
    */
}