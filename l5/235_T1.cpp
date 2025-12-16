#include<iostream>
#include<string>
#include<array>
#include<random>

using namespace std;

class Pizza {
    private:
        string pizzaName;
        // one of Thin, Thick or Stuffed
        string crustType;
        int spicinessLevel;
        bool isExtraCheesy;

    public:
    Pizza() {
        pizzaName = "Unnamed";
        crustType = "Unnamed";
        spicinessLevel = 0;
        isExtraCheesy = false;
    }

    Pizza(string name, string crust, int spiciness, bool extraCheesy) {
        pizzaName = name;
        crustType = crust;
        spicinessLevel = spiciness;
        isExtraCheesy = extraCheesy;
    }

    string getPizzaName() const {
        return pizzaName;
    }

    string getCrustType() const {
        return crustType;
    }

    int getSpicinessLevel() const {
        return spicinessLevel;
    }

    bool getIsExtraCheesy() const {
        return isExtraCheesy;
    }

    void setPizzaName(string name) {
        pizzaName = name;
    }

    void setCrustType(string ctype) {
        if (ctype != "Thin" && ctype != "Thick" && ctype != "Stuffed") {
            cout << "Invalid crust type provided";
            ctype = "Thin";
        }
        crustType = ctype;
    }

    void setSpicinessLevel(int lvl) {
        if (lvl < 1 || lvl > 10) {
            cout << "Invalid spiciness level";
            lvl = 5;
        }

        spicinessLevel = lvl;
    }

    void setIsExtraCheesy(bool val) {
        isExtraCheesy = val;
    }

    void displayDetails() const {
        cout << "Pizza: " << pizzaName << "\n";
        cout << "Crust type: " << crustType << "\n";
        cout << "Spiciness: " << spicinessLevel << "\n";
        cout << "Is Extra Cheesy: " << (isExtraCheesy ? "True" : "False") << endl;
    }
};

void prepareOrders(array<Pizza, 30>& menu, int size) {
    string name, crust;
    int spiciness;
    bool cheesy;

    for (int i = 0; i < size; i++) {
        cout << "Provide pizza name: ";
        cin >> name;
        cout << "Crust Type (Thin, Thick, Stuffed): ";
        cin >> crust;
        cout << "Spiciness (1-10): ";
        cin >> spiciness;
        cout << "Put extra cheese: ";
        cin >> cheesy;
        cout << endl;
        Pizza p(name, crust, spiciness, cheesy);
        menu[i] = p;
    }
}

Pizza fillPizza(bool isCheesy) {
    int s = rand() % 10 + 1;
    Pizza p = Pizza("Mystery Pizza", "Thick", s, isCheesy);
    return p;
}

int main() {
    srand(0);
    array<Pizza, 30> menu;
    prepareOrders(menu, 4);
    for (int i = 4; i < 30; i++) {
        menu[i] = fillPizza(i % 2 == 0);
    }

    for (int i = 0; i < 30; i++) {
        Pizza p = menu[i];
        if (p.getSpicinessLevel() >= 7) {
            p.displayDetails();
        }
    }
    return 0;
}