#include <iostream>
#include <string>
using namespace std;

class IGadget {
   public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

class IConnected {
   public:
    virtual void connectToWiFi() = 0;
    virtual void disconnectWiFi() = 0;
};

class BasicGadget : public IGadget {
   private:
    string gadgetName;

   public:
    BasicGadget(string name) : gadgetName(name) {}
    void turnOn() {
        cout << "Basic turn on" << endl;
    }

    void turnOff() {
        cout << "Basic turn off" << endl;
    }

    void showName() {
        cout << "Gadget Name: " << gadgetName << endl;
    }
};

class SmartGadget : public IGadget, public IConnected {
   private:
    string gadgetName;
    int batteryLevel;

   public:
    SmartGadget(string name, int battery = 50) : gadgetName(name), batteryLevel(battery) {}

    void turnOn() {
        cout << "Smart gadget turned on." << endl;
        cout << "Battery level: " << batteryLevel << "%" << endl;
    }

    void turnOff() {
        cout << "Smart gadget turned off." << endl;
    }

    void connectToWiFi() {
        cout << "Connecting to WiFi..." << endl;
    }

    void disconnectWiFi() {
        cout << "Disconnecting from WiFi..." << endl;
    }

    void chargeBattery(int amount) {
        batteryLevel += amount;
        if (batteryLevel > 100) batteryLevel = 100;
        cout << "Battery level: " << batteryLevel << "%" << endl;
    }

    void reduceBattery(int amount) {
        batteryLevel -= amount;
        if (batteryLevel < 0) batteryLevel = 0;
        cout << "Battery level: " << batteryLevel << "%" << endl;
    }

    int getBatteryLevel() const {
        return batteryLevel;
    }
};

class AdvancedRobot : public SmartGadget {
   private:
    string robotID;

   public:
    AdvancedRobot(string name, string id) : SmartGadget(name), robotID(id) {}

    void turnOn() {
        SmartGadget::turnOn();
        cout << "Robot " << robotID << " is powered up." << endl;
    }

    void scanEnvironment() {
        cout << "Scanning environment..." << endl;
    }

    void moveForward(int steps) {
        cout << "Robot " << robotID << " moved " << steps << " steps forward." << endl;
    }

    void performSelfCheck() {
        cout << "Robot " << robotID << " performing self-check..." << endl;
    }

    void displayBattery() const {
        cout << "Battery level: " << getBatteryLevel() << "%" << endl;
    }
};

void test(IGadget* t) {
    t->turnOn();
    t->turnOff();
}

int main() {
    AdvancedRobot rob("Bumblebee", "AB-002");
    rob.turnOn();
    rob.chargeBattery(20);
    rob.connectToWiFi();
    rob.scanEnvironment();
    rob.moveForward(5);
    rob.performSelfCheck();
    rob.disconnectWiFi();
    rob.turnOff();
    rob.displayBattery();
    rob.reduceBattery(10);
    

    // test
    BasicGadget bg("Basic Gadget");
    SmartGadget sg("Smart Gadget");
    AdvancedRobot ar("Advanced Robot", "AR-001");

    test(&bg);
    test(&sg);
    test(&ar);
    
    return 0;
}