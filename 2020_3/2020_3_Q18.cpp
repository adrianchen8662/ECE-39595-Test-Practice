#include <vector>
#include <iostream>

class Observer {
public:
    virtual void update(int i)=0;
};

class Subject {
    virtual void subscribe(Observer* o)=0;
    virtual void remove(Observer* o)=0;
};

class Buss : public Subject {
private:
    std::vector<Observer*> observers;
public:
    Buss( );
    virtual void subscribe(Observer* o);
    virtual void remove(Observer* o);
    virtual void notify(int i) const;
    virtual void putDataOnBuss(int i) const;
};

Buss::Buss( ) {
    observers = std::vector<Observer*>( );
}

void Buss::subscribe(Observer* o) {
    observers.push_back(o);
}

void Buss::remove(Observer* o) {
    std::vector<Observer*>::iterator it =
    std::find(observers.begin( ),
        observers.end( ), o);
    if (it != observers.end( ))
        observers.erase(it);
}

void Buss::notify(int i) const {
    for (Observer* o : observers) {
        o->update(i);
    }
}

void Buss::putDataOnBuss(int i) const {
    notify(i);
}

class OutputPort : public Observer {
private:
    int portId = -1;
public:
    OutputPort(int i);
    virtual void update(int i);
};

OutputPort::OutputPort(int i) {
    portId = i;
}

void OutputPort::update(int i) {
    std::cout << "Output port " << portId;
    std::cout << " receives " << i << std::endl;
}

void writeData(const Buss& buss,
                int low, int high) {
    for (int i = low; i < high; i++) {
        buss.putDataOnBuss(i);
    }
}

int main(int argc, char** args) {
    Buss buss;
    OutputPort* port1 = new OutputPort(1);
    OutputPort* port2 = new OutputPort(2);
    buss.subscribe(port1);
    buss.subscribe(port2);
    writeData(buss, 10, 12);

    buss.remove(port2);
    writeData(buss, 8, 10);

    buss.subscribe(new OutputPort(3));
    writeData(buss, 6, 8);
}

// Q18 - What is the name of the pattern used in this program?
/*
    Either Observer or Publish/Subscribe
*/