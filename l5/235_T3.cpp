#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Wizard {
   private:
    string wizardName;
    string familiarType;
    int spellPower;
    int manaPool;

   public:
    Wizard() {
        wizardName = "Unnamed";
        familiarType = "Unnamed";
        spellPower = 0;
        manaPool = 0;
    }

    Wizard(string name, string familiar, int power, int mana) {
        wizardName = name;
        familiarType = familiar;
        spellPower = power;
        manaPool = mana;
    }

    double arcane(Wizard op) {
        return pow(spellPower, 0.8) * (manaPool / (manaPool + op.spellPower)) + log(spellPower + 1) * sqrt(manaPool);
    }

    Wizard duel(Wizard op) {
        Wizard self = Wizard(this->wizardName, this->familiarType, this->spellPower, this->manaPool);
        double a1 = arcane(op);
        double a2 = op.arcane(self);
        if (a1 > a2) {
            return self;
        } else {
            return op;
        }
    }

    string getName() const {
        return wizardName;
    }
};

int main() {
    array<Wizard, 5> w;
    w[0] = Wizard("Merlin", "Owl", 85, 200);
    w[1] = Wizard("Gandalf", "Owl", 90, 180);
    w[2] = Wizard("Dumbledore", "Owl", 88, 190);
    w[3] = Wizard("Saruman", "Owl", 82, 170);
    w[4] = Wizard("Morgana", "Owl", 87, 185);

    for (int i = 0; i < 4; i++) {
        Wizard w1 = w[i];
        Wizard w2 = w[i + 1];
        cout << "Round " << i + 1 << " " << w1.getName() << " vs " << w2.getName() << "\n";
        w[i + 1] = w1.duel(w2);
        cout << "Winner: " << w[i + 1].getName() << endl;
    }
    
    return 0;
}