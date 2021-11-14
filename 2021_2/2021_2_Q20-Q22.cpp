#include <string>
#include <iostream>

// Except.h
class Except {
public:
    std::string msg;
    Except(std::string);
};

// Except.h
Except::Except(std::string m) {
    msg = m;
}

// Obj.h
class Obj {
public:
    std::string msg;
    Obj( );
    Obj(std::string m);
};

// Obj.cpp
Obj::Obj( ) {
    msg = "";
}

Obj::Obj(std::string m) : msg(m) { }

// main.cpp
void f2(Obj* p) {
    if (p == nullptr) {throw new Except("null p");}
    if (p->msg == "") {throw new std::string("no msg");}
    std::cout << p->msg << std::endl;
}

void f1(Obj* p) {
    try {
        f2(p);
    } catch (Except* e) {std::cout << e->msg << std::endl;}
        catch (std::string* s) {std::cout << *s << std::endl;}
}

int main(int argc, char** args) {

    Obj* op1 = new Obj("safe");
    Obj* op2 = nullptr;
    Obj* op3 = new Obj( );

    f1(op1); // Q20 - safe
    /*
        The object was declared with a message of "safe"
    */
    f1(op2); // Q21 - null p
    /*
        The object was declared as a null pointer
    */
    f1(op3); // Q22 - no msg
    /*
        The object was declared with no message
    */
}