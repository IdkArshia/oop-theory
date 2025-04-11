#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    int id;
    string name;
    bool cardStatus;

public:
    User(int id=0, string name=""): id(id), name(name), cardStatus(false) {}

    virtual void payFees() = 0;

    virtual void displayInfo() const {
        cout<<"ID:"<<id<<"|Name:"<<name<<"|Card:"<<(cardStatus?"Active":"Inactive")<<endl;
    }

    void tapCard() {
        if(cardStatus) {
            cout<<"Access granted to "<<name<<"."<<endl;
        } else {
            cout<<"Access denied. Please pay the fee, "<<name<<"."<<endl;
        }
    }

    int getID() const { return id; }
};

class Student : public User {
    string assignedStop;

public:
    Student(int id=0, string name=""): User(id, name) {}

    void assignStop(string stop) { assignedStop = stop; }

    void payFees() override {
        cardStatus = true;
        cout<<"Semester fee paid by student:"<<name<<"."<<endl;
    }

    void displayInfo() const override {
        User::displayInfo();
        cout<<"Assigned Stop:"<<assignedStop<<endl;
    }
};

class Teacher : public User {
    double monthlyFee;

public:
    Teacher(int id=0, string name="", double fee=0.0): User(id, name), monthlyFee(fee) {}

    void payFees() override {
        cardStatus = true;
        cout<<"Monthly fee paid by teacher:"<<name<<"."<<endl;
    }
};

class Staff : public User {
    double monthlyFee;

public:
    Staff(int id=0, string name="", double fee=0.0): User(id, name), monthlyFee(fee) {}

    void payFees() override {
        cardStatus = true;
        cout<<"Monthly fee paid by staff:"<<name<<"."<<endl;
    }
};

const int MAX_USERS = 100;

class BusStop {
    int stopID;
    string location;
    User* assignedUsers[MAX_USERS];
    int userCount;

public:
    BusStop(int id=0, string loc="") {
        stopID = id;
        location = loc;
        userCount = 0;
    }

    void assignUser(User* user) {
        if(userCount < MAX_USERS) {
            assignedUsers[userCount++] = user;
        }
    }

    string getLocation() const { return location; }

    void getStopDetails() const {
        cout<<"Stop:"<<location<<"|Users Assigned:"<<userCount<<endl;
    }
};

const int MAX_STOPS = 50;

class Route {
    int routeID;
    string busNumber;
    BusStop stops[MAX_STOPS];
    int stopCount;

public:
    Route(int id=0, string bus="") {
        routeID = id;
        busNumber = bus;
        stopCount = 0;
    }

    void addStop(const BusStop& stop) {
        if(stopCount < MAX_STOPS) {
            stops[stopCount++] = stop;
        }
    }

    void getRouteDetails() const {
        cout<<"Route ID:"<<routeID<<"|Bus No:"<<busNumber<<"|Total Stops:"<<stopCount<<endl;
    }

    bool operator==(const Route& other) const {
        return routeID==other.routeID && busNumber==other.busNumber && stopCount==other.stopCount;
    }
};

class TransportationSystem {
    User* users[MAX_USERS];
    int userCount;

public:
    TransportationSystem() { userCount = 0; }

    void registerUser(User* user) {
        if(userCount < MAX_USERS) {
            users[userCount++] = user;
            cout<<"User registered:"<<user->getID()<<endl;
        }
    }

    void processPayment(int id) {
        for(int i=0; i<userCount; ++i) {
            if(users[i]->getID()==id) {
                users[i]->payFees();
                return;
            }
        }
        cout<<"User with ID "<<id<<" not found."<<endl;
    }

    void recordAttendance(int id) {
        for(int i=0; i<userCount; ++i) {
            if(users[i]->getID()==id) {
                users[i]->tapCard();
                return;
            }
        }
        cout<<"No record found for ID:"<<id<<"."<<endl;
    }
};

int main() {
    TransportationSystem system;
    Student* s1 = new Student(1, "Areeba");
    Teacher* t1 = new Teacher(2, "Sir Saad", 3000);
    Staff* st1 = new Staff(3, "Mr.Tariq", 2500);
    system.registerUser(s1);
    system.registerUser(t1);
    system.registerUser(st1);
    system.processPayment(1);
    system.processPayment(2);
    system.recordAttendance(1);
    system.recordAttendance(2);
    system.recordAttendance(3);
    Route r1(10, "BUS-123");
    Route r2(10, "BUS-123");
    if(r1==r2)
        cout<<"Routes are the same."<<endl;
    else
        cout<<"Routes are different."<<endl;
    return 0;
}
