#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class FileOpenException : public exception {
   private:
    string filename;

   public:
    FileOpenException(string filename = "") : filename(filename) {}
};

class MalformedPatientRecordException : public exception {
   private:
    string record;

   public:
    MalformedPatientRecordException(string record = "") : record(record) {}
};

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

    static void deserialize(const string& data, Patient& patient) {
        int pos = 0;
        int nextPos = data.find('|', pos);
        if (nextPos == string::npos) throw MalformedPatientRecordException(data);
        patient.id = stoi(data.substr(pos, nextPos - pos));
        // id
        pos = nextPos + 1;

        nextPos = data.find('|', pos);
        if (nextPos == string::npos) throw MalformedPatientRecordException(data);
        // name
        patient.name = data.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        nextPos = data.find('|', pos);
        if (nextPos == string::npos) throw MalformedPatientRecordException(data);
        // age
        patient.age = stoi(data.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        nextPos = data.find('|', pos);
        if (nextPos == string::npos) throw MalformedPatientRecordException(data);
        // gender
        patient.gender = data.substr(pos, nextPos - pos)[0];
        pos = nextPos + 1;

        nextPos = data.find('|', pos);
        if (nextPos == string::npos) throw MalformedPatientRecordException(data);
        // blood group
        patient.bloodGroup = data.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        // contact
        patient.contact = data.substr(pos);

        if (pos >= data.size()) throw MalformedPatientRecordException(data);
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

template <typename T, int MAX>
class FileRepository {
   private:
    T items[MAX];
    int itemCount;
    string filename;

   public:
    FileRepository(string filename) : filename(filename), itemCount(0) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw FileOpenException(filename);
        }
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
            throw FileOpenException(filename);
        }

        file << item.serialize() << endl;
        if (file.fail()) {
            throw FileOpenException(filename);
        }
        file.close();
        items[itemCount] = item;
        itemCount++;
        return true;
    }

    int load() {
        ifstream file(filename);
        if (!file.is_open()) {
            throw FileOpenException(filename);
        }

        string line;
        itemCount = 0;
        while (getline(file, line) && itemCount < MAX) {
            T item;
            try {
                T::deserialize(line, item);
                items[itemCount++] = item;
            } catch (const MalformedPatientRecordException& e) {
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
    try {
        FileRepository<Patient, 100> repo("patients.txt");

        Patient p1(1, "Alice Johnson", 21, 'F', "O+", "0123456789");
        Patient p2(2, "Bob Khan", 23, 'M', "A-", "0987654321");

        repo.add(p1);
        repo.add(p2);

        int count = repo.load();
        repo.printAll(cout);
    } catch (const FileOpenException& e) {
        cerr << "Error opening file: " << e.what() << endl;
    } catch (const MalformedPatientRecordException& e) {
        cerr << "Malformed patient record: " << e.what() << endl;
    } catch (...) {
        cerr << "An unexpected error occurred." << endl;
    }
    return 0;
}