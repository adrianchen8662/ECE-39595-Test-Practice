#include <string>
#include <ostream>
#include <iostream>

class Stringy {

private:
    std::string stringData;
public:
    Stringy(std::string _data);
    Stringy(const Stringy& old);
    Stringy& operator=(const Stringy& s);
    Stringy& operator+(const Stringy& s) const;
    Stringy& operator+=(const Stringy& s);
    Stringy& operator-(int i) const;
    std::string getData( ) const;
    friend Stringy& operator*(const Stringy & s, int n);
    friend std::ostream& operator<< (
        std::ostream& os, const Stringy& s);
};

Stringy::Stringy(std::string _data) {
    stringData = _data;
}

Stringy::Stringy(const Stringy& old) {
    stringData = old.getData( ) + "a";
}

Stringy& Stringy::operator=(const Stringy& s) {
    stringData = s.getData( );
    Stringy* stringy = new Stringy("return");
    return *stringy;
}

Stringy& Stringy::operator+(const Stringy& s) const {
    Stringy* stringy =
        new Stringy(stringData + s.getData( ));
    return *stringy;
}

Stringy& Stringy::operator+=(const Stringy& s) {
    stringData = stringData + s.getData( );
    return *this;
}

Stringy& Stringy:operator-(int i) const {
    int newLen = (stringData.size( ) - i) + 1;
    Stringy* retVal;
    if (newLen >= 0) {
        retVal = new Stringy(
            stringData.substr(0,newLen));
    }
}

std::string Stringy::getData( ) const {
    return stringData;
}

std::ostream& operator<<(
        std::ostream& os, const Stringy& s) {
    return os << s.getData( );
}

int main(int argc, char** argv) {
    Stringy a("a");
    Stringy b("b");
    Stringy c("c");
    Stringy s1(a);
    std::cout << s1 << std::endl; // Q1 - aa
    /*
        constructor adds an a
    */
    a = b = c;
    std::cout << a << std::endl // Q2 - return
    /*
        equals operator overrides
    */
    std::cout << b << std::endl; // Q3 - c
    /*

    */
    Stringy d("ddd");
    Stringy e("eee");
    std::cout << d+e << std::endl; // Q4 - dddeee
    /*
        operator overloading
    */
    std::cout << e-1 << std::endl; // Q5 - eee
    /*
        not defined operator overload, minus 1 does nothing
    */
    Stringy f("f");
    std::cout << f*3 << std::endl; // Q6 - fff
    /*
        operator overloading
    */
    Stringy s2 = d += e;
    std::cout << s2 << std::endl; // Q7 - dddeeea
    /*
        s2 = adds an a, d+= e adds ddd and eee to make dddeeea
    */
    std::cout << d << std::endl; // Q8 - dddeee
    /*
        d += e is done first, reassigning d to dddeee. s2 = brings in the a
    */
}

// Q9 - In operator+, what does the first const mean?
// B. the object passed in as s cannot be changed
/*
    B
*/

// Q10 - In operator+, what does the second const mean?
// A. the object pointed to by this cannot be changed
/*
    A
*/

// Q11 - In perator+, in the expression "getData + s.getData()", what is the + operator?
// B. the std::string concatenation operator
/*
    B
*/
