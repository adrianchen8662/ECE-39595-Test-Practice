#include <ostream>
#include <string>
#include <iostream>

class Err {
protected:
    std::string msg;
public:
    Err(std::string _msg);
    friend std::ostream& operator<<(
        std::ostream& os, const Err& e);
};

Err::Err(std::string _msg) {
    msg = _msg;
}

std::ostream& operator<<(std::ostream& os,
                        const Err& e) {
    return os << "Err: " << e.msg;
}

class MyException : public Err {
public:
    MyException(std::string msg);
    friend std::ostream& operator<<(
        std::ostream& os, const MyException& e);
};

MyException::MyException(std::string msg) : Err(msg) { }

ostream& operator<<(ostream& os, const MyException& e) {
    return os << "My: " << e.msg;
}

void f(int j) {
    if (j==0) {
        throw MyException("0");
    }
    if (j == 1) {
        throw Err("1");
    }
    if (j == 2) {
        throw 2;
    }
}

int main( ) {
    for (int i = 0; i < 2; i++) {
        try {
            f(i);
        } catch (MyException meobj) {
            std::cout << meobj << std::endl; // S1
        } catch (Err eobj) {
            std::cout << eobj << std::endl; // S2
        }
    }
}
// Q5 - For S1, say what it prints if S1 executes, and "nothing" if it is not executed. 
/*
    My: 0
*/

// Q6 - For S2, say what it prints if S2 executes, and "nothing" if it is not executed.
/*
    Err: 1
*/
