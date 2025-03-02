#include <iostream>
#include <string>

using namespace std;

class Vehicle 
{
private:
    string model;
    double rentalPrice;
    string lincenseRequired;

public:
    Vehicle(string m, double price, string l)
    {
        model = m;
        rentalPrice = price;
        lincenseRequired = l;
    }

    string getModel() const
    {
        return model;
    }

    double getRentalPrice() const
    {
        return rentalPrice;
    }

    string getRequiredLicense() const
    {
        return lincenseRequired;
    }

    void setModel(const string& m)
    {
        model = m;
    }

    void setRentalPrice(double price)
    {
        rentalPrice = price;
    }

    void setRequiredLicense(const string& license)
    {
        lincenseRequired = license;
    }
};

class User 
{
private:
    int userID;
    string name;
    int age;
    string licenseType;
    string contactInfo;

public:
    User(int id, string n, int a, string license, string contact)
    {
        userID = id;
        name = n;
        age = a;
        licenseType = license;
        contactInfo = contact;
    }

    int getUserID() const
    {
        return userID;
    }

    string getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    string getLicenseType() const
    {
        return licenseType;
    }

    string getContactInfo() const
    {
        return contactInfo;
    }

    void setUserID(int id)
    {
        userID = id;
    }

    void setName(const string& n)
    {
        name = n;
    }

    void setAge(int a)
    {
        age = a;
    }

    void setLicenseType(const string& license)
    {
        licenseType = license;
    }

    void setContactInfo(const string& contact)
    {
        contactInfo = contact;
    }

    bool canRent(Vehicle* vehicle)
    {
        return licenseType == vehicle->getRequiredLicense();
    }
};

class RentalSystem 
{
private:
    Vehicle** vehicles;
    int vehicleCount;
    int vehicleCapacity;

public:
    RentalSystem() 
    {
        vehicleCount = 0;
        vehicleCapacity = 2;
        vehicles = new Vehicle*[vehicleCapacity];
    }

    ~RentalSystem() 
    {
        for (int i = 0; i < vehicleCount; i++) 
        {
            delete vehicles[i];
        }

        delete[] vehicles;
    }

    int getVehicleCount() const
    {
        return vehicleCount;
    }

    void registerUser(User* user)
    {
        cout << "User " << user->getName() << " registered." << endl;
    }

    void addVehicle(Vehicle* vehicle)
    {
        if (vehicleCount == vehicleCapacity) 
        {
            vehicleCapacity *= 2;
            Vehicle** newVehicles = new Vehicle*[vehicleCapacity];

            for (int i = 0; i < vehicleCount; i++) 
            {
                newVehicles[i] = vehicles[i];
            }

            delete[] vehicles;
            vehicles = newVehicles;
        }

        vehicles[vehicleCount++] = vehicle;
    }

    void rentVehicle(User* user, Vehicle* vehicle)
    {
        if (user->canRent(vehicle)) 
        {
            cout << user->getName() << " rented " << vehicle->getModel() 
                 << " for $" << vehicle->getRentalPrice() << " per day." << endl;
        } 
        else 
        {
            cout << user->getName() << " cannot rent " << vehicle->getModel() 
                 << " due to license restrictions." << endl;
        }
    }
};

int main() 
{
    User user1(1, "Arshia", 18, "Full", "124-589-6770");
    Vehicle* vehicle1 = new Vehicle("civic", 50.0, "Full");
    Vehicle* vehicle2 = new Vehicle("meera", 70.0, "Intermediate");
    RentalSystem system;
    system.registerUser(&user1);
    system.addVehicle(vehicle1);
    system.addVehicle(vehicle2);
    system.rentVehicle(&user1, vehicle1);
    system.rentVehicle(&user1, vehicle2);

    return 0;
}
