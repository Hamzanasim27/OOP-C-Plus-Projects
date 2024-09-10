#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

class Parking_lot
{
public:
    string username;
    string password;

    Parking_lot() {}

    void outlook()
    {
        cout << "\n\n\n\n\n\n\n\t\t\t\t$$ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ $$\n";
        cout << "\t\t\t\t$$ ___________ $$\n";
        cout << "\t\t\t\t$$|                                           		                                  |$$\n";
        cout << "\t\t\t\t$$|                                           		                                  |$$\n";
        cout << "\t\t\t\t$$|                                           		                                  |$$\n";
        cout << "\t\t\t\t$$|                                     Parking Lot                                       |$$\n";
        cout << "\t\t\t\t$$|                                                                                       |$$\n";
        cout << "\t\t\t\t$$|                                  Management System                                    |$$\n";
        cout << "\t\t\t\t$$|                                                                                       |$$\n";
        cout << "\t\t\t\t$$|                                                                                       |$$\n";
        cout << "\t\t\t\t$$|___________|$$\n";
        cout << "\t\t\t\t$$ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ $$\n\n\n\n\t\t\t\t\t";

    p:
        int choice;
        cout << "\t \t ...Login page..." << endl;
        cout << "\n1. Create new User" << endl;
        cout << "\n2. Login current user" << endl;
        cout << "\n3. Exit" << endl;
        cout << "\n \n Choose any option you want:" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            create_user();
            break;
        case 2:
            login_user();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "\t \n invalid value please try again(press any key)" << endl;
            goto p;
        }
    }

    void create_user()
    {
        // open the file for writing (creating it if it doesn't exist)
        fstream file("credentials.txt", ios::out);

        // prompt the user to enter a username and password
        cout << "Enter a username: ";
        cin >> username;

        file << username << endl;

        cout << "Enter a password: ";
        cin >> password;

        file << password << endl;

        cout << "\n\n\t\t user created successfully";
        file.close();
    }
    void login_user()
    {
        string user;
        string pass;
        // open the file for writing (creating it if it doesn't exist)

        fstream file("credentials.txt", ios::in);

        file >> username >> password;

        cout << "Enter Username: " << endl;
        cin >> user;

        cout << "Enter Password: " << endl;
        cin >> pass;

        if (user == username && pass == password)
        {
            cout << "\n\n\t\t user Login successfully";
            cout << "\n\n\n\n\t\t\t\t  Access Granted! Welcome To Our System \n\n";
        }
        else
        {
            cout << "\n\n\n\n\t\t\t\t\tAccess Aborted...Please Try Again!!\n";
            outlook();
        }
        file.close();
    }
};

class Vehicle
{
public:
    string owner;
    string vehicleName;
    string numberPlate;
    time_t entryTime;
    time_t exitTime;
    bool parked;

public:
    Vehicle(string own, string name, string plate)
        : owner(own), vehicleName(name), numberPlate(plate), parked(false) {}

    virtual float calculateCharges() = 0;

    void enter()
    {
        entryTime = time(nullptr);
        parked = true;
        auto now = chrono::system_clock::now();
        time_t now_time_t = chrono::system_clock::to_time_t(now);
        tm local_tm;
        localtime_s(&local_tm, &now_time_t);
        int hours = local_tm.tm_hour;
        int minutes = local_tm.tm_min;
        cout << "Vehicle entered parking lot at: " << hours << ":" << minutes << endl;
    }

    void exit()
    {
        if (!parked)
        {
            cout << "Error: Vehicle is not parked!" << endl;
            return;
        }
        exitTime = time(nullptr);
        parked = false;
        auto now = chrono::system_clock::now();
        time_t now_time_t = chrono::system_clock::to_time_t(now);
        tm local_tm;
        localtime_s(&local_tm, &now_time_t);
        int hours = local_tm.tm_hour;
        int minutes = local_tm.tm_min;
        cout << "Vehicle exited parking lot at: " << hours << ":" << minutes << endl;
        time_t duration = exitTime - entryTime;
        cout << "Duration of parking: " << duration / 60 << " minutes." << endl;
    }

    virtual void displayInfo()
    {
        cout << endl;
        cout << "Owner: " << owner << endl;
        cout << "Vehicle Name: " << vehicleName << endl;
        cout << "Number Plate: " << numberPlate << endl;
    }

    friend ofstream& operator<<(ofstream& ofs, Vehicle& vehicle);
};

// Child class Car
class Car : public Vehicle
{
public:
    float charges;

    Car(string own, string name, string plate)
        : Vehicle(own, name, plate) {}

    float calculateCharges()
    {
        time_t duration = exitTime - entryTime;
        int hours = duration / 3600;
        charges = 50 * (hours + 1); // Charging for each hour started
        return charges;
    }
};

// Child class Bike
class Bike : public Vehicle
{
public:
    float charges;

    Bike(string own, string name, string plate)
        : Vehicle(own, name, plate) {}

    float calculateCharges()
    {
        time_t duration = exitTime - entryTime;
        int hours = duration / 3600;
        charges = 30 * (hours + 1); // Charging for each hour started
        return charges;
    }
};

// Child class Bus
class Bus : public Vehicle
{
public:
    float charges;

    Bus(string own, string name, string plate)
        : Vehicle(own, name, plate) {}

    float calculateCharges()
    {
        time_t duration = exitTime - entryTime;
        int hours = duration / 3600;
        charges = 80 * (hours + 1); // Charging for each hour started
        return charges;
    }
};

// Overloading the insertion operator to save vehicle information to file
ofstream& operator<<(ofstream& ofs, Vehicle& vehicle)
{
    ofs << "\n";
    ofs << "Owner: " << vehicle.owner << endl;
    ofs << "Vehicle Name: " << vehicle.vehicleName << endl;
    ofs << "Number Plate: " << vehicle.numberPlate << endl;
    return ofs;
}

int main()
{
    Parking_lot A;
    A.outlook();

    string owner, vehicleName, numberPlate;

    int car_count = 0;
    int bike_count = 0;
    int bus_count = 0;
    char ch;

    do
    {
        int choice;
        cout << "\t \t ...Select..." << endl;
        cout << "\n1. CAR" << endl;
        cout << "\n2. BIKE" << endl;
        cout << "\n3. BUS" << endl;
        cout << "\n4. To EXIT" << endl;
        cout << "\n \n Enter Your choice: " << endl;
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
        {
            cout << "Enter owner name: " << endl;
            cin >> owner;
            cout << "Enter vehicle name: " << endl;
            cin >> vehicleName;
            cout << "Enter number plate: " << endl;
            cin >> numberPlate;

            Car car(owner, vehicleName, numberPlate);
            car.enter();

            char ch;
            cout << "Press any key when you want to exit the parking lot..." << endl;
            cin >> ch;
            car.exit();

            float charges_Car = car.calculateCharges();
            car.displayInfo();
            cout << "Parking Charges: Rs" << charges_Car << endl;
            cout << endl;

            // Saving vehicle information to a file
            ofstream File1("parking_info.txt", ios::app);
            if (File1.is_open())
            {
                File1 << endl;
                File1 << car;
                File1 << "Charges: Rs" << charges_Car << endl;
                File1.close();
            }
            else
            {
                cout << "Unable to open file." << endl;
                return 0;
            }
            car_count++;
        }
        break;
        case 2:
        {
            cout << "Enter owner name: " << endl;
            cin >> owner;
            cout << "Enter vehicle name: " << endl;
            cin >> vehicleName;
            cout << "Enter number plate: " << endl;
            cin >> numberPlate;

            Bike bike(owner, vehicleName, numberPlate);
            bike.enter();

            char ch;
            cout << "Press any key when you want to exit the parking lot..." << endl;
            cin >> ch;
            bike.exit();

            float charges_Bike = bike.calculateCharges();
            bike.displayInfo();
            cout << "Parking Charges: Rs" << charges_Bike << endl;
            cout << endl;

            // Saving vehicle information to a file
            ofstream File2("parking_info.txt", ios::app);
            if (File2.is_open())
            {
                File2 << endl;
                File2 << bike;
                File2 << "Charges: Rs" << charges_Bike << endl;
                File2.close();
            }
            else
            {
                cout << "Unable to open file." << endl;
                return 0;
            }
            bike_count++;
        }
        break;
        case 3:
        {
            cout << "Enter owner name: " << endl;
            cin >> owner;
            cout << "Enter vehicle name: " << endl;
            cin >> vehicleName;
            cout << "Enter number plate: " << endl;
            cin >> numberPlate;

            Bus bus(owner, vehicleName, numberPlate);
            bus.enter();

            char ch;
            cout << "Press any key when you want to exit the parking lot..." << endl;
            cin >> ch;
            bus.exit();

            float charges_Bus = bus.calculateCharges();
            bus.displayInfo();
            cout << "Parking Charges: Rs" << charges_Bus << endl;
            cout << endl;

            // Saving vehicle information to a file
            ofstream File3("parking_info.txt", ios::app);
            if (File3.is_open())
            {
                File3 << endl;
                File3 << bus;
                File3 << "Charges: Rs" << charges_Bus << endl;
                File3.close();
            }
            else
            {
                cout << "Unable to open file." << endl;
                return 0;
            }
            bus_count++;
        }
        break;
        }
        cout << "Do you want to enter more vehicles(y/n): " << endl;
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    char Ch;
    cout << "Do you want to see how many Cars, Bikes and Buses arrived today(y/n): " << endl;
    cin >> Ch;
    if (Ch == 'y' || Ch == 'Y')
    {
        cout << car_count << " Cars arrived today." << endl;
        cout << bike_count << " Bikes arrived today." << endl;
        cout << bus_count << " Buses arrived today." << endl;
        cout << "\t\t...Good Bye..." << endl;
    }
    else
    {
        cout << "\t\t...Good Bye..." << endl;
    }
}