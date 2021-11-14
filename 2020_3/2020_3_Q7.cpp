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
    try {
        f(2);
    } catch (MyException meobj) {
        std::cout << "caught MyException\n";
    } catch (Err eobj) {
        std::cout << "caught Err" << std::endl;
    }
    std::cout << "done." << std::endl; // S1
}

// Q7 - Does S1 execute? 
/*
    No
*/