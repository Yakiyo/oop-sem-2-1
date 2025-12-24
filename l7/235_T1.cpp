#include <iostream>
#include <string>
using namespace std;

class Person {
   private:
    static int idCounter;
    string name;
    int age;
    int personID;

   public:
    Person() : name("John Doe"), age(0), personID(idCounter++) {}
    Person(const string name, int age) : name(name), age(age), personID(idCounter++) {}

    ~Person() {
        cout << "~Person() is called" << endl;
    }

    void displayDetails() const {
        cout << name << ", Age: " << age << ", P_ID: " << personID << endl;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    int getPersonID() const {
        return personID;
    }

    void setName(string name) {
        this->name = name;
    }

    void setAge(int age) {
        this->age = age;
    }

    void setPersonID(int id) {
        this->personID = id;
    }

    bool operator==(const Person& other) const {
        return (name == other.name) && (age == other.age);
    }

    friend ostream& operator<<(ostream& out, const Person& self);
};

ostream& operator<<(ostream& out, const Person& self) {
    out << self.name << ", Age: " << self.age << ", P_ID: " << self.personID << endl;
    return out;
}

int Person::idCounter = 1;

class Student : public Person {
   private:
    int sid;

   public:
    Student() : Person(), sid(0) {}

    Student(string name, int age, int sid) : Person(name, age), sid(sid) {}

    int getSid() const {
        return sid;
    }

    void setSid(int sid) {
        this->sid = sid;
    }
};

class Faculty : public Person {
   private:
    string designation;

   public:
    Faculty() : Person("Mr. X", 22), designation("Lecturer") {}

    Faculty(string name, int age, string designation) : Person(name, age), designation(designation) {}

    ~Faculty() {
        cout << "~Faculty() is called" << endl;
    }

    string getDesignation() const {
        return designation;
    }

    void setDesignation(string designation) {
        this->designation = designation;
    }
};

class Visitor : private Person {
   private:
    string visitingPurpose;

   public:
    Visitor() : Person(), visitingPurpose("Tourist") {}
    Visitor(string visitingPurpose) : Person(), visitingPurpose(visitingPurpose) {}

    string getVisitingPurpose() const {
        return visitingPurpose;
    }

    void setVisitingPurpose(string visitingPurpose) {
        this->visitingPurpose = visitingPurpose;
    }
};

///// TESTING FUNCTIONS //////

void TestPerson() {
    Person p1, p2("Faisal", 30);

    if (p1.getName() == "John Doe" && p1.getAge() == 0 && p1.getPersonID() == 1)
        cout << "Zero Arg Constructor - Passed" << endl;
    else
        cout << "Zero Arg Constructor - Failed!!!!" << endl;

    if (p2.getName() == "Faisal" && p2.getAge() == 30 && p2.getPersonID() == 2)
        cout << "Argumented Constructor - Passed" << endl;
    else
        cout << "Argumented Constructor - Failed!!!!" << endl;

    if (p1 == p1)
        cout << " operator == - Passed" << endl;
    else
        cout << " operator == - Failed!!!!" << endl;
}

void TestStudent() {
    Student s1;
}
void TestFaculty() {
    Faculty f;
    if (f.getName() == "Mr. X" && f.getAge() == 22 && f.getDesignation() == "Lecturer")
        cout << "Zero Arg Constructor Faculty - Passed" << endl;
    else
        cout << "Zero Arg Constructor Faculty - Failed!!!!" << endl;
}
void TestVisitor() {
    Visitor v;
}

int main() {
    TestPerson();
    TestStudent();
    TestFaculty();
    TestVisitor();
}

// int main() {
//     Person p1;

//     cout << p1.getName() << endl;

//     p1.setName("Dumbledore");
//     p1.setAge(91);

//     cout << p1;

//     Student s1;
//     Student s2("Raihan", 21, 233);
//     Person p2("Maverick", 72);
//     cout << s2 << p2;

//     Visitor v1("Conference");

//     // does not allow access as we inherited privately
//     // v1.getName();
//     return 0;
// }