#include <iostream>

using namespace std;

class DigitalWallet {
   private:
    double ID;
    double balance;

    bool isOverDraft() const {
        return balance < 0;
    }

   public:
    DigitalWallet(double ownerID, double currentBalance = 0) : ID(ownerID), balance(currentBalance) {}
    
    ~DigitalWallet() {
        cout << "Current balance for " << ID << " is " << balance << endl;
    }

    double getID() const {
        return ID;
    }

    double getBalance() const {
        return balance;
    }

    void setID(double newID) {
        ID = newID;
    }

    void setBalance(double newBalance) {
        if (newBalance < 0) {
            cout << "Cannot set a negative balance" << endl;
            return;
        }
        balance = newBalance;
    }

    // val to the right
    DigitalWallet operator+(double val);

    // val to the left
    friend DigitalWallet operator+(double val, const DigitalWallet& self);

    DigitalWallet operator-(double val);

    DigitalWallet operator*(double interest);

    operator long() const;

    void printWallet() const {
        cout << "ID: " << ID << " Balance: " << balance << endl;
    }
};


DigitalWallet DigitalWallet::operator+(double val) {
    return DigitalWallet(this->getID(), this->getBalance() + val);
}

DigitalWallet operator+(double val, const DigitalWallet& self) {
    return DigitalWallet(self.getID(), self.getBalance() + val);
}

DigitalWallet DigitalWallet::operator-(double val) {
    DigitalWallet dn(this->getID(), this->getBalance() - val);
    if (dn.isOverDraft()) {
        cout << "Negative balance reached!" << endl;
    }

    return dn;
}

DigitalWallet DigitalWallet::operator*(double interest) {
    return DigitalWallet(this->getID(), this->getBalance() * interest);
}

DigitalWallet::operator long() const {
    return static_cast<long>(this->balance * 100);
}

int main() {
    DigitalWallet w1(1, 55), w2(2, 64);
    w1.printWallet();
    w2.printWallet();

    w2 = w1 + 50.0;
    w1.printWallet();
    w2.printWallet();

    w2 = w1 * 1.05;
    w2.printWallet();
    w2 = w1 - 58.0;
    w2.printWallet();
    return 0;
}