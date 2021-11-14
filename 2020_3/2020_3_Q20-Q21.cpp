#include <string>
#include <iostream>

class Disk {
private:
    std::string diskType;
public:
    Disk(std::string type);
    virtual std::string type( );
};

Disk::Disk(std::string type) {
    diskType = type;
}

std::string Disk::type( ) {
    return diskType;
}

class SSDDrive : public Disk {
public:
    SSDDrive( );
};

SSDDrive::SSDDrive( ) : Disk("SSD") { }

class SpinningDrive : public Disk {
public:
    SpinningDrive( );
};

SpinningDrive::SpinningDrive( ) :
    Disk("Spinning") { }

class Computer {
private:
    Disk* disk = nullptr;
public:
    Computer( );
    Computer(Disk* d);
    virtual void changeDisk(Disk* d);
    virtual std::string readDisk(int addr);
};

Computer::Computer( ) {
    disk = nullptr;
}

Computer::Computer(Disk* d) {
    disk = d;
}

void Computer::changeDisk(Disk* d) {
    disk = d;
}

std::string Computer::readDisk(int addr) {
    std::string str = std::string("reading addr ");
    str += std::to_string(addr);
    str += std::string(" on ")+disk->type( );
    str += std::string(" disk");
    return str;
}

int main(int argc, char** args) {
    Computer c;
    for (int i = 1; i < argc; i++) {
        std::string diskType = args[i];
        if (diskType.compare("ssd") == 0) {
            c = Computer(new SSDDrive( ));
        } else if (diskType.compare("spin") == 0) {
            c = Computer(new SpinningDrive( ));
        }
        std::cout << "read disk: " << c.readDisk(i);
    }
}

// Q20 - What pattern is used in Program C?
/*
    Strategy
*/

//Q21 - What classes would need to be changed if a new type of Disk is added? Answer with the letters for all changed classes.
// E. the main function
/*
    E
*/

