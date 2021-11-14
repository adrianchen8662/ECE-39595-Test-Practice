#include <vector>
#include <iostream>

class OutputPort {
private:
    int portId = -1;
public:
    OutputPort(int i);
    virtual void write(int i);
};

OutputPort::OutputPort(int i) {
    portId = i;
}

void OutputPort::write(int i) {
    std::cout << "Output port " << portId << " receives " << i << std::endl;
}

class Buss {
private:
    std::vector<OutputPort> ports;
    int len = -1;
public:
    Buss(int len, int portIds[ ]);
    virtual void notify(int i);
    virtual void putDataOnBuss(int i);
};

Buss::Buss(int len, int portIds[ ]) {
    ports = std::vector<OutputPort>( );
    for (int i = 0; i < len; i++) {
        ports.push_back(OutputPort(i));
    }
}

void Buss::notify(int i) {
    for (OutputPort p : ports) {
        p.write(i);
    }
}

void Buss::putDataOnBuss(int i) {
    notify(i);
}

int main(int argc, char** args) {
    int portIds[ ] = {1, 3, 2};
    Buss buss = Buss(3, portIds);

    buss.putDataOnBuss(6);
    buss.putDataOnBuss(7);
}

// Q19 -  Let it be true that the Buss will never have Output ports added or removed. We know that patterns often add complexity. Given these, should Program A or Program B be used in this case?
/*
    Program B
*/