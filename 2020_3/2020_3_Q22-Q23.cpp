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

class ComputerBuilder {
public:
    static Computer build(std::string driveType);
};

Computer ComputerBuilder::build(
    1std::string driveType) {
    Computer c;
    if (driveType.compare("ssd") == 0) {
        c = Computer(new SSDDrive( ));
    } else if (driveType.compare("spin") == 0) {
        c = Computer(new SpinningDrive( ));
    }
    return c;
}

int main(int argc, char** args) {
    for (int i = 1; i < argc; i++) {
        Computer c = ComputerBuilder::build(args[i]);
        std::cout << "reading: ";
        std::cout << c.readDisk(i) << std::endl;
    }
}

// Q22 - What pattern is used in Program D?
/*
    Either Factory or Factory Method
*/

// Q23 - What classes would need to be changed if a new type of Disk is added?
// E. ComputerBuilder
/*
    E
*/