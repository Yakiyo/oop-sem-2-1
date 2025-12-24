#include<iostream>

using namespace std;

class SocialPost {
    private:
    int ID;
    int likes;
    int shares;

    int viralScore() const {
        return likes + shares * 3;
    }
    public:
    SocialPost(int postId, int postLikes, int postShares) {
        if (postLikes < 0) {
            cout << "Cannot be negative" << endl;
            postLikes = 0;
        }
        if (postShares < 0) {
            cout << "Cannot be negative" << endl;
            postShares = 0;
        }
        ID = postId;
        likes = postLikes;
        shares = postShares;
    }
    
    int getID() const {
        return ID;
    }

    int getLikes() const {
        return likes;
    }

    int getShares() const {
        return shares;
    }

    void setID(int id) {
        ID = id;
    }

    void setLikes(int newLikes) {
        if (newLikes < 0) {
            cout << "Cannot be negative" << endl;
        }
        likes = newLikes;
    }

    void setShares(int newShares) {
        if (newShares < 0) {
            cout << "Cannot be negative" << endl;
        }
        shares = newShares;
    }

    SocialPost& operator+=(int add) {
        this->likes += add;
        return *this;
    }

    SocialPost& operator-=(int sub) {
        this->likes -= sub;
        return *this;
    }

    bool operator==(const SocialPost& other) const {
        return this->ID == other.ID && this->likes == other.likes && this->shares == other.shares;
    }

    bool operator>(const SocialPost& other) const {
        return this->viralScore() > other.viralScore();
    }

    bool operator<(const SocialPost& other) const {
        return this->viralScore() < other.viralScore();
    }

    void printStatus() const {
        cout << "ID     :" << ID << "\n";
        cout << "Likes  :" << likes << "\n";
        cout << "Shares :" << shares << endl;
    }
};

int main() {
    SocialPost p1(1, 5, 3), p2(1, 4, 4);
    p1.printStatus();
    p2.printStatus();

    cout << ((p1 > p2) ? "p1 gt p2" : "p2 gt p1") << endl;

    cout << ((p1 == p2) ? "Eq" : "Neq") << endl;

    p2 += 2;
    p2.printStatus();
    p1 -= 1;
    p1.printStatus();
    return 0;
}