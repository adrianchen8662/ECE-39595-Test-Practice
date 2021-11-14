#include <ostream>
#include <iostream>

template <typename T, typename U>
    class Pair {
private:
    T data1;
    U data2;
public:
    Pair(T t, U u);
    bool operator<(const Pair<T,U>& p);
    friend std::ostream operator<<(
        std::ostream& os,
        const Pair<T, U>& p) {
        os << "(" << p.data1 << ", ";
        os << p.data2 << ")";
        return os;
    }
};

template <typename T, typename U>
    Pair<T, U>::Pair(const T t, const U u) :
        data1(t), data2(u) { }

template <typename T, typename U>
    bool Pair<T, U>::operator<(
        const Pair<T, U>& p) {
    if (data1 < p.data2) return true;
    return ((data1 == p.data1) &&
            (data2 < p.data2));
}

class Obj {
private:
    int data;
public:
    Obj(int);
    virtual bool operator<(const Obj& obj);
    virtual bool operator<(int i);
    virtual bool operator==(const Obj& obj);
    virtual bool operator==(int i);
};

Obj::Obj(int i) : data(i) { }

bool Obj::operator<(const Obj& obj) {
    return data < obj.data;
}

bool Obj::operator<(int i) {
    return data < i;
}

bool Obj::operator==(const Obj& obj) {

}

bool Obj::operator==(int i) {
    return data == i;
}

class C {
public:
    C( );
};

C::C( ) { }

int main(int argc, char** args) {
    Pair<int,int> ipair1 = Pair<int,int>(1,1);
    Pair<int,int> ipair2 = Pair<int,int>(2,2);
    std::cout << (ipair1 < ipair2) << std::endl; // Q24 - 1 or true

    Pair<Obj,Obj> opair1 = Pair<Obj,Obj>(Obj(2),Obj(1));
    Pair<Obj,Obj> opair2 = Pair<Obj,Obj>(Obj(1),Obj(2));
    std::cout << (opair1 < opair2) << std::endl;

    Pair<Obj,int> oipair1 = Pair<Obj,int>(Obj(1),1); // S1
    Pair<Obj,int> oipair2 = Pair<Obj,int>(Obj(2),2);
    std::cout << (oipair1 < oipair2) << std::endl; // Q25 - 1 or true

    Pair<C,C> ccpair1 = Pair<C,C>(C( ),C( ));
    Pair<C,C> ccpair2 = Pair<C,C>(C( ),C( ));
    std::cout << (ccpair1 < ccpair2) << std::endl; // Q26 - Err
}

// Q27 - What is the type of data1 in the Pair at S1?
/*
    Obj
*/

//Q28 - What is the type of data2 in the Pair at S2?
/*
    int
*/

//Q29 - What function or operation is used for “<” at the statement of Q25? Give the function name and arguments (e.g., foo(int, int) if a function, and say “primitive” if it is a built-in “<” operation.
/*
    operator<(const Obj& obj)
*/