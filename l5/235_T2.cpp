#include <iostream>
#include <string>
#include <vector>
#include <array>
using namespace std;

class GymProfile {
   private:
    string memberName;
    string memberTier;
    double bodyWeight;
    double benchPressMax;

    public:
        GymProfile(string name, string tier, double weight, double benchPress) {
            memberName = name;
            memberTier = tier;
            bodyWeight = weight;
            benchPressMax = benchPress;
        }

        GymProfile() {
            memberName = "N/A";
            memberTier = "N/A";
            bodyWeight = 0.0;
            benchPressMax = 0.0;
        }

        string getMemberName() const {
            return memberName;
        }

        string getMemberTier() const {
            return memberTier;
        }

        double getBodyWeight() const {
            return bodyWeight;
        }

        double getBenchPressMax() const {
            return benchPressMax;
        }

        void setMemberName(string name) {
            memberName = name;
        }

        void setMemberTier(string tier) {
            if (tier.size() <= 3) {
                tier = "Standard";
            }
            memberTier = tier;
        }

        void setBodyWeight(double w) {
            if (w < 40 || w > 200) {
                w = 70.0;
            }

            bodyWeight = w;
        }

        void setBenchPressMax(double bp) {
            benchPressMax = bp;
        }

        void completeSession() {
            bodyWeight -= 1.5;
            benchPressMax *= 1.05;
        }

        void displayStats() const {
            cout << "Name: "<< memberName << endl;
            cout << "Tier: " << memberTier << endl;
            cout << "Weight: " << bodyWeight << endl;
            cout << "Bench Press: " << benchPressMax << endl;
        }
};

void completeTrainingSession(GymProfile& profile) {
    profile.completeSession();
}

int main() {
    array<GymProfile, 5> members;
    for (int i = 0; i < 5; i++) {
        GymProfile p = GymProfile("A", "Max Tier", 72, 80);
        members[i] = p;

        p.displayStats();
        completeTrainingSession(p);
        p.displayStats();
    }
    return 0;
}