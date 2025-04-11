#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    int vehicleID;
    double speed;
    double maxWeight;
    double efficiency;
    static int activeDeliveries;
public:
    Vehicle(int id, double spd = 1.0, double maxWt = 1.0) : vehicleID(id), speed(spd), maxWeight(maxWt) {
        efficiency = speed * maxWeight;
        activeDeliveries++;
        cout <<"Vehicle "<<vehicleID<<" activated. Total active deliveries: "<<activeDeliveries<<endl;
    }
    virtual ~Vehicle() {
        activeDeliveries--;
        cout <<"Vehicle "<<vehicleID<<" deactivated. Total active deliveries: "<<activeDeliveries<<endl;
    }

    virtual void calculateRoute(const string &destination) {
        cout<<"Base optimal route to "<<destination<<endl;
    }

    virtual void estimatedTime(const string &destination) {
        cout<<"estimated time: 30 minutes\n";
    }
    virtual void move() = 0;
    virtual void command(const string &action, int packageID) {
        cout << "Vehicle "<<vehicleID<<" performing action: "<<action 
        <<" for package "<<packageID<<endl;
    }

    virtual void command(const string &action, int packageID, const string &urgencyLevel) {
        cout<<"Vehicle "<<vehicleID <<" performing action: "<<action 
        <<" for package "<<packageID<<" with urgency level: "<<urgencyLevel<<endl;
    }

    void operator==(const Vehicle &other) const {
        if (efficiency == other.efficiency) {
            cout<<"Vehicle "<<vehicleID<<" and Vehicle "<<other.vehicleID<<" are equally efficient."<<endl;
        } 
		else if (speed > other.speed) {
            cout<<"Vehicle "<<vehicleID<<" is faster than Vehicle "<<other.vehicleID<<"."<<endl;
        } 
		else{
            cout<<"Vehicle "<<other.vehicleID<<" is faster than Vehicle "<<vehicleID<<"." <<endl;
        } 
        
    }
};

int Vehicle::activeDeliveries = 0;
class RamzanDrone:public Vehicle {
public:
    RamzanDrone(int id):Vehicle(id, 5.0, 2.0) { }
    void calculateRoute(const string &destination) override {
        cout<<"Aerial route for rapid delivery to "<<destination<<endl;
    }
    void estimatedTime(const string &destination) override {
        cout<<"estimated delivery time: 10 minutes\n";
    }
    void move() override {
        cout<<"RamzanDrone "<<vehicleID<<" reaching destination through the skies"<<endl;
}
    void command(const string &action, int packageID) override {
        cout<<"RamzanDrone "<<vehicleID<<" processing command: "<<action 
        <<" for package "<<packageID<<" (drone standard mode)"<<endl;
    }
    void command(const string &action, int packageID, const string &urgencyLevel) override {
        if (urgencyLevel=="urgent") {
            cout<<"RamzanDrone "<<vehicleID<<" activating high-speed mode for package " 
            <<packageID<<" delivering iftar on time"<<endl;
        } else {
            cout<<"RamzanDrone "<<vehicleID<<" processing command with normal priority."<<endl;
        }
    }
};
class RamzanTimeShip:public Vehicle {
public:
    RamzanTimeShip(int id) : Vehicle(id, 3.0, 4.0) { }
    void calculateRoute(const string &destination) override {
        cout<<"Time travel route to historical "<<destination<<endl;
    }

    void estimatedTime(const string &destination) override {
        cout<<"estimated delivery time: 20 minutes\n";
    }

    void move() override {
        cout<<"RamzanTimeShip "<<vehicleID<<" travelling through time"<<endl;
    }
    void command(const string &action, int packageID) override {
        cout<<"RamzanTimeShip "<<vehicleID<<" scheduling command: "<<action 
        <<" for package "<<packageID<<endl;
    }

    void command(const string &action, int packageID, const string &urgencyLevel) override {
        if (urgencyLevel == "urgent") {
            cout<<"RamzanTimeShip "<<vehicleID<<" validating historical integrity for urgent package " 
            << packageID<<" before departure."<<endl;
        } else {
            cout<<"RamzanTimeShip "<<vehicleID<<" processing scheduled delivery for package " 
            <<packageID<<endl;
        }
    }
};

class RamzanHyperPod : public Vehicle {
public:
    RamzanHyperPod(int id) : Vehicle(id, 4.0, 6.0) { }
    void calculateRoute(const string &destination) override {
        cout<<"Underground route to "<<destination<<endl;
    }
    void estimatedTime(const string &destination) override {
        cout<<"estimated delivery time:15 minutes\n";
    }
    void move() override {
        cout<<"RamzanHyperPod "<<vehicleID<<" going through underground tunnels"<<endl;
    }
    void command(const string &action, int packageID) override {
        cout<<"RamzanHyperPod "<<vehicleID<<" processing bulk delivery command for package " 
        <<packageID<<endl;
    }

    void command(const string &action, int packageID, const string &urgencyLevel) override {
        cout<<"RamzanHyperPod "<<vehicleID<<" received command for package "<<packageID 
        <<" with urgency level: "<<urgencyLevel<<". Processing with high capacity mode."<<endl;
    }
};

int main() {
    RamzanDrone drone1(101);
    RamzanTimeShip timeShip1(202);
    RamzanHyperPod hyperPod1(303);
   string destination="fast University";
   drone1.calculateRoute(destination);
   drone1.estimatedTime(destination);
   timeShip1.calculateRoute(destination);
   timeShip1.estimatedTime(destination);
   hyperPod1.calculateRoute(destination);
   hyperPod1.estimatedTime(destination);
    cout << "\n";
    drone1.move();
    timeShip1.move();
    hyperPod1.move();
    cout << "\n";
    drone1.command("Deliver", 1001);
    timeShip1.command("Deliver", 2002);
    hyperPod1.command("Deliver", 3003);
    drone1.command("Deliver", 1002, "urgent");
    timeShip1.command("Deliver", 2003, "urgent");
    hyperPod1.command("Deliver", 3004, "urgent");
    cout << "\n";
    drone1 == hyperPod1;
   timeShip1 == drone1;
    return 0;
}
