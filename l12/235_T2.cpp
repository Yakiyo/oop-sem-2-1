#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class Patient {
   private:
    int id;
    string name;
    int age;
    char gender;
    string bloodGroup;
    string contact;

   public:
    Patient(int id = 1, string name = "", int age = 0, char gender = 'M', string bloodGroup = "O-", string contact = "") {
        this->id = id;
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->bloodGroup = bloodGroup;
        this->contact = contact;
    }

    string serialize() const {
        return to_string(id) + "|" + name + "|" + to_string(age) + "|" + gender + "|" + bloodGroup + "|" + contact;
    }

    static bool deserialize(const string& data, Patient& patient) {
        int pos = 0;
        int nextPos = data.find('|', pos);
        if (nextPos == string::npos) return false;
        patient.id = stoi(data.substr(pos, nextPos - pos));
        // id
        pos = nextPos + 1;

        nextPos = data.find('|', pos);
        if (nextPos == string::npos) return false;
        // name
        patient.name = data.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        nextPos = data.find('|', pos);
        if (nextPos == string::npos) return false;
        // age
        patient.age = stoi(data.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        nextPos = data.find('|', pos);
        if (nextPos == string::npos) return false;
        // gender
        patient.gender = data.substr(pos, nextPos - pos)[0];
        pos = nextPos + 1;

        nextPos = data.find('|', pos);
        if (nextPos == string::npos) return false;
        // blood group
        patient.bloodGroup = data.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        // contact
        patient.contact = data.substr(pos);

        if (pos >= data.size()) return false;
        return true;
    }

    static void printHeader(ostream& os) {
        os << "| ID | Name                 | Age | Gender | Blood | Contact       |" << endl;
    }

    void printRow(ostream& os) const {
        os << "| " << left
           << setw(2) << id << " | "
           << setw(20) << name << " | "
           << setw(3) << age << " | "
           << setw(6) << gender << " | "
           << setw(5) << bloodGroup << " | "
           << setw(13) << contact << " |" << endl;
    }

    static void sep(ostream& os) {
        os << setfill('-') << setw(68) << "" << setfill(' ') << endl;
    }
};

bool appendPatientToFile(const string& filename, const Patient& p) {
    ofstream file(filename, ios::app);

    if (!file.is_open()) {
        cerr << "Error opening file for writing." << endl;
        return false;
    }

    file << p.serialize() << endl;

    if (file.fail()) {
        cerr << "Error writing to file." << endl;
        return false;
    }

    file.close();
    return true;
}

int loadAllPatient(const string& filename, Patient arr[], int maxCount) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return -1;
    }

    string line;
    int count = 0;
    while (getline(file, line) && count < maxCount) {
        Patient p(0, "", 0, ' ', "", "");
        if (Patient::deserialize(line, p)) {
            arr[count++] = p;
        } else {
            cerr << "Error deserializing patient data: " << line << endl;
        }
    }
    file.close();
    return count;
}
template <typename T, int MAX>
class FileRepository {
   private:
    T items[MAX];
    int itemCount;
    string filename;

   public:
    FileRepository(string filename) : filename(filename), itemCount(0) {
        ofstream file(filename);
        file << "";  // Clear the file
        file.close();
    }

    bool add(const T& item) {
        if (itemCount >= MAX) {
            cerr << "Repository is full." << endl;
            return false;
        }

        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cerr << "Error opening file for writing." << endl;
            return false;
        }

        file << item.serialize() << endl;
        if (file.fail()) {
            cerr << "Error writing to file." << endl;
            return false;
        }
        file.close();
        items[itemCount] = item;
        itemCount++;
        return true;
    }

    int load() {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file for reading." << endl;
            return -1;
        }

        string line;
        itemCount = 0;
        while (getline(file, line) && itemCount < MAX) {
            T item;
            if (T::deserialize(line, item)) {
                items[itemCount++] = item;
            } else {
                cerr << "Error deserializing data: " << line << endl;
            }
        }
        file.close();
        return itemCount;
    }

    int count() const {
        return itemCount;
    }

    void printAll(ostream& os) const {
        T::sep(os);
        T::printHeader(os);
        T::sep(os);
        for (int i = 0; i < itemCount; i++) {
            items[i].printRow(os);
        }
        T::sep(os);
    }
};

int main() {
    FileRepository<Patient, 100> repo("patients.txt");

    Patient p1(1, "Alice Johnson", 21, 'F', "O+", "0123456789");
    Patient p2(2, "Bob Khan", 23, 'M', "A-", "0987654321");

    repo.add(p1);
    repo.add(p2);

    int count = repo.load();
    repo.printAll(cout);
    return 0;
}