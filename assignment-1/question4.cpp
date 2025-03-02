#include <iostream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_STOPS = 50;
class Student {
private:
    int studentID;
    string name;
    bool cardStatus;
    string assignedStop;

public:
    Student(int id = 0, string n = "") {
        studentID = id;
        name = n;
        cardStatus = false;
    }

    int getID() const { return studentID; }
    string getName() const { return name; }
    bool isCardActive() const { return cardStatus; }
    string getAssignedStop() const { return assignedStop; }
    void assignStop(const string& stop) { assignedStop = stop; }
    void payFees() {
        cardStatus = true;
        cout << "Payment successful. Card activated for " << name << "." << endl;
    }

    void tapCard() {
        if (cardStatus) {
            cout << "Attendance recorded for " << name << "." << endl;
        } else {
            cout << "Access denied. Payment required for " << name << "." << endl;
        }
    }

    void displayInfo() const {
        cout << "ID: " << studentID << " | Name: " << name << " | Stop: " << assignedStop
             << " | Card: " << (cardStatus ? "Active" : "Inactive") << endl;
    }
};

class BusStop {
private:
    int stopID;
    string location;
    Student* assignedStudents[MAX_STUDENTS];
    int studentCount;
public:
    BusStop(int id = 0, string loc = "") {
        stopID = id;
        location = loc;
        studentCount = 0;
    }

    void assignStudent(Student* student) {
        if (studentCount < MAX_STUDENTS) {
            assignedStudents[studentCount++] = student;
            student->assignStop(location);
        }
    }

    void getStopDetails() const {
        cout << "Stop: " << location << "  Total Students: " << studentCount << endl;
    }
};

class Route {
private:
    int routeID;
    BusStop stops[MAX_STOPS];
    int stopCount;
    string busNumber;

public:
    Route(int id = 0, string bus = "") {
        routeID = id;
        busNumber = bus;
        stopCount = 0;
    }

    void addStop(const BusStop& stop) {
        if (stopCount < MAX_STOPS) {
            stops[stopCount++] = stop;
        }
    }

    void getRouteDetails() const {
        cout << "Route: " << routeID << "  Bus No: " << busNumber << "  Stops: " << stopCount << endl;
    }
};

class TransportationSystem {
private:
    Student students[MAX_STUDENTS];
    int studentCount;

public:
    TransportationSystem() {
        studentCount = 0;
    }

    void registerStudent(int id, string name) {
        if (studentCount < MAX_STUDENTS) {
            students[studentCount++] = Student(id, name);
            cout << "Student registered: " << name << "." << endl;
        } else {
            cout << "Registration failed. Maximum student limit reached." << endl;
        }
    }

    void processPayment(int id) {
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].getID() == id) {
                students[i].payFees();
                return;
            }
        }
        cout << "Student not found with ID: " << id << "." << endl;
    }

    void recordAttendance(int id) {
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].getID() == id) {
                students[i].tapCard();
                return;
            }
        }
        cout << "No record found for student ID: " << id << "." << endl;
    }
};

int main() {
    TransportationSystem system;

    system.registerStudent(101, "Arshia");
    system.registerStudent(102, "Zara");
    system.processPayment(101);
    system.recordAttendance(101);
    system.recordAttendance(102);

    return 0;
}
