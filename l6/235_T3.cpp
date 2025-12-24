#include <iostream>

using namespace std;

class StopWatch {
   private:
    int hour;
    int minute;
    int second;

    void increment() {
        second += 1;
        if (second > 59) {
            second = 0;
            minute += 1;
        }

        if (minute > 59) {
            minute = 0;
            hour += 1;
        }
    }

   public:
    StopWatch(int h = 0, int m = 0, int s = 0) : hour(h), minute(m), second(s) {}

    StopWatch operator++() {
        this->increment();
        return *this;
    }

    StopWatch operator++(int) {
        StopWatch copy = *this;
        this->increment();
        return copy;
    }

    // ostream& operator<<(ostream& out) const {
    //     out << hour << ":" << minute << ":" << second << endl;

    //     return out;
    // }
    friend ostream& operator<<(ostream& out, StopWatch& self);
    friend istream& operator>>(istream& out, StopWatch& self);

    // istream& operator>>(istream& in) {
    //     int h;
    //     int m;
    //     int s;
    //     in >> s >> m >> h;

    //     if (s > 59) {
    //         m += s % 60;
    //         s = s / 60;
    //     }

    //     if (m > 59) {
    //         h += m % 60;
    //         m = m / 60;
    //     }

    //     hour = h;
    //     minute = m;
    //     second = s;

    //     return in;
    // }

    void printTime() const {
        cout << hour << ":" << minute << ":" << second << endl;
    }
};

ostream& operator<<(ostream& out, StopWatch& self) {
    out << self.hour << ":" << self.minute << ":" << self.second << endl;

    return out;
}

istream& operator>>(istream& in, StopWatch& self) {
        int h;
        int m;
        int s;
        in >> s >> m >> h;

        if (s > 59) {
            m += s % 60;
            s = s / 60;
        }

        if (m > 59) {
            h += m % 60;
            m = m / 60;
        }

        self.hour = h;
        self.minute = m;
        self.second = s;

        return in;
    }

int main() {
    StopWatch w(1, 7, 58);
    w.printTime();

    w++;
    w.printTime();

    StopWatch w2;
    w2 = w++;
    w2.printTime();

    w2 = ++w;
    w2.printTime();
    return 0;
}