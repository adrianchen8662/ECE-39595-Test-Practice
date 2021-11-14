#include <ostream>
#include <iostream>
#include <vector>

// List.h
template <class T> class List {
private:
    std::vector<T> list;
public:
    List( );
    void insert(T d);
    T getHead( ) const;
    int size( ) const;
    template<typename T1>
    friend std::ostream& operator<<(
        std::ostream& os, List<T1> l);
};

template<class T> List<T>::List( ) { }

template<class T> void
    List<T>::insert(const T d) {
    list.push_back(d);
}

template<class T> T List<T>::getHead( ) const {
    return list.front( );
}

template<class T> int List<T>::size( ) const {
    return list.size( );
}

// prints the list members in the order entered
template<class T1> std::ostream& operator<<(
    std::ostream& os, List<T1> l) {
    for (size_t i=0; i<l.size( ); i++) {
        os << l.list[i] << " ";
    }
    return os;
}

// Obj.h
class Obj {
private:
    int data;
public:
    Obj(int i);
    friend std::ostream& operator<<(
        std::ostream& os, Obj o);
};

// Obj.cpp
Obj::Obj(int i) : data(i) { }

std::ostream& operator<<(
    std::ostream& os, Obj o) {
    
    os << o.data << " "; // S1
    return os;  
}

// main.cpp
int main(int argc, char** args) {
    List<int> intList; // S2
    List<Obj> objList; // S3
    for (int i=0; i<4; i++) {
        intList.insert(i);
    }
    std::cout << intList << std::endl; // Q4 - 0 1 2 3 (counted reverse order)
    /*
        intList is a vector of ints, and insert into the list. Inserted in order, printed in order 
    */

    intList.insert(Obj(1)); // Err
    /*
        wrong type being inserted
    */

    for (int i=0; i<4; i++) {
        objList.insert(Obj(i));
    }
    std::cout << objList << std::endl; // Q6 - 0 1 2 3 (counted reverse order)
    /*
        objList is a vector of objects, and inserted into the list. Inserted in order, printed in order
    */
}

// Q7 - What is the type of data in the list of S2?
/*
    int
*/

// Q8 - What is the type of data in the list of S3?
/*
    Obj
*/

// Q9 - When printing an Obj in statement S1 in Obj.cpp, what operator << is called on o.data?
// a. the operator << defined for int by C++
// c. the operator << defined for Obj in Obj.cpp
/*
    a
    The statement S1 is inside the ostream operator, so the operator is still the default one defined in C++, not the overloaded one
*/