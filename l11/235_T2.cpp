#include <iostream>
#include <string>
using namespace std;

class IPlayer {
   public:
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
};

class IStreamable {
   public:
    virtual void connectToInternet() = 0;
    virtual void disconnectInternet() = 0;
};

class BasicPlayer : public IPlayer {
   private:
    string playerName;

   public:
    BasicPlayer(string name) : playerName(name) {}

    void play() {
        cout << "Playing content" << endl;
    }

    void pause() {
        cout << "Pausing content" << endl;
    }

    void stop() {
        cout << "Stopping content" << endl;
    }

    void showName() const {
        cout << "Player Name: " << playerName << endl;
    }
};

class SmartPlayer : public IPlayer, public IStreamable {
   private:
    string playerName;
    int volumeLevel;

   public:
    SmartPlayer(string name, int volume = 20) : playerName(name), volumeLevel(volume) {}

    void play() {
        cout << "Playing at " << volumeLevel << "%" << endl;
    }

    void pause() {
        cout << "Pausing content" << endl;
    }

    void stop() {
        cout << "Stopping content" << endl;
    }

    void connectToInternet() {
        cout << "Connecting to Internet..." << endl;
    }

    void disconnectInternet() {
        cout << "Disconnecting from Internet..." << endl;
    }

    void adjustVolume(int amount) {
        volumeLevel += amount;
        if (volumeLevel > 100) volumeLevel = 100;
        if (volumeLevel < 0) volumeLevel = 0;
        cout << "Volume level: " << volumeLevel << "%" << endl;
    }

    void showVolume() const {
        cout << "Volume level: " << volumeLevel << "%" << endl;
    }

    int getVolume() const {
        return volumeLevel;
    }
};

class AdvancedDJ : public SmartPlayer {
   private:
    string djName;

   public:
    AdvancedDJ(string name, string djName) : SmartPlayer(name), djName(djName) {}

    void play() {
        SmartPlayer::play();
        cout << "DJ " << djName << " is mixing tracks!" << endl;
    }

    void mixTracks() {
        cout << "Mixing tracks..." << endl;
    }

    void setPlaylist(string playlist) {
        cout << "Playlist set to: " << playlist << endl;
    }
};

int main() {
    AdvancedDJ dj("SuperPlayer", "DJ MixMaster");

    dj.connectToInternet();
    dj.play();
    dj.mixTracks();
    dj.setPlaylist("Top Hits 2025");
    dj.pause();
    dj.adjustVolume(10);
    dj.stop();
    
    return 0;
}