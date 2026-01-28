#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SpellCaster {
   private:
    int basePowerLevel;
    string casterName;
    int health;

   public:
    SpellCaster(string name, int powerLevel = 1, int health = 100) {
        basePowerLevel = powerLevel;
        casterName = name;
        this->health = health;
    }

    void scout() {
        cout << casterName << " is scouting the area for enemies." << endl;
    }

    virtual int castSpell() {
        cout << casterName << " is casting a generic spell..." << endl;
        return basePowerLevel;
    }

    virtual void takeDamage(int damage) {
        health -= damage;
        cout << casterName << " took " << damage << " damage. Remaining health: " << health << endl;
    }

    bool isAlive() {
        return health > 0;
    }
};

class Pyromancer : public SpellCaster {
   private:
    int heatIntensity;

   public:
    Pyromancer(string name, int powerLevel = 1, int heatIntensity = 0, int health = 100) : SpellCaster(name, powerLevel, health) {
        this->heatIntensity = heatIntensity;
    }

    int castSpell() {
        int base = SpellCaster::castSpell();
        cout << "Adding fire element..." << endl;

        return base + heatIntensity;
    }

    void scout() {
        SpellCaster::scout();
    }

    void takeDamage(int damage) {
        SpellCaster::takeDamage(damage * 2);
    }
};

class LavaMage : public Pyromancer {
   private:
    int magmaDensity;

   public:
    LavaMage(string name, int powerLevel = 1, int heatIntensity = 0, int magmaDensity = 0, int health = 100) : Pyromancer(name, powerLevel, heatIntensity, health) {
        this->magmaDensity = magmaDensity;
    }

    int castSpell() {
        cout << "Solidifying magma..." << endl;

        return magmaDensity + Pyromancer::castSpell();
    }

    void ignite() {
        cout << "The ground is burning!" << endl;
    }

    void takeDamage(int damage) {
        SpellCaster::takeDamage(damage * 3);
    }
};

class Enemy {
   private:
    string name;
    int health;
    int armor;

   public:
    Enemy(string name, int health = 100, int armor = 10) {
        this->name = name;
        this->health = health;
        this->armor = armor;
    }

    virtual void takeDamage(int damage) {
        health -= 0.8 * damage;
        armor -= 0.2 * damage;
    }

    virtual string getType() {
        return "Enemy";
    }

    int getHealth() {
        return health;
    }

    virtual bool isAlive() {
        return health > 0;
    }

    virtual int attack() {
        return 10;
    }
};

class Ogre : public Enemy {
   private:
    bool rageMode;

   public:
    Ogre(string name, int health = 60, int armor = 50) : Enemy(name, health, armor) {
        rageMode = false;
    }

    int attack() {
        cout << "Ogre is attacking" << endl;

        return rageMode ? 25 : 20;
    }

    void takeDamage(int damage) {
        Enemy::takeDamage(damage);

        if (getHealth() < 5) {
            rageMode = true;
        }
    }

    string getType() {
        return "Ogre";
    }
};

int randInt(int max) {
    return rand() % max;
}

bool aliveEnemy(vector<Enemy*> enemies) {
    for (auto enemy : enemies) {
        if (enemy->isAlive()) {
            return true;
        }
    }
    return false;
}

bool aliveCaster(vector<SpellCaster*> casters) {
    for (auto caster : casters) {
        if (caster->isAlive()) {
            return true;
        }
    }
    return false;
}

int main() {
    SpellCaster* spellCaster = new SpellCaster("Gandalf", 5);
    SpellCaster* pyromancer = new Pyromancer("Pyro", 7, 10);
    SpellCaster* lavaMage = new LavaMage("Lava", 10, 15, 20);

    vector<SpellCaster*> casters = {spellCaster, pyromancer, lavaMage};

    Enemy* ogre0 = new Ogre("Gorg");
    Enemy* ogre1 = new Ogre("Unga");
    Enemy* ogre2 = new Ogre("Thok");

    vector<Enemy*> enemies = {ogre0, ogre1, ogre2};

    srand(time(0));

    while (true) {
        Enemy* enemy = enemies[randInt(enemies.size())];

        while(!enemy->isAlive()) {
            enemy = enemies[randInt(enemies.size())];
        }

        for (auto caster : casters) {
            if (!caster->isAlive()) continue;
            enemy->takeDamage(caster->castSpell());
        }

        if (!aliveEnemy(enemies)) {
            cout << "Spell Casters win!" << endl;
            break;
        }

        SpellCaster* caster = casters[randInt(casters.size())];
        while(!caster->isAlive()) {
            caster = casters[randInt(casters.size())];
        }

        caster->takeDamage(enemy->attack());

        if (!aliveCaster(casters)) {
            cout << "Enemies win!" << endl;
            break;
        }
    }

    return 0;
}