#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DisplayUnit {
   private:
    float screenSize;
    string resolution;

   public:
    DisplayUnit(float screenSize = 65, string resolution = "4K") {
        this->screenSize = screenSize;
        this->resolution = resolution;
    }

    float getScreenSize() const {
        return screenSize;
    }

    string getResolution() const {
        return resolution;
    }

    void setScreenSize(float size) {
        screenSize = size;
    }

    void setResolution(string res) {
        resolution = res;
    }

    ~DisplayUnit() {
        cout << "Display unit turned off" << endl;
    }

    void showVisuals() const {
        cout << "Displaying content at " << resolution << " on " << screenSize << " inches screen" << endl;
    }
};

class ComputingUnit {
   private:
    string processorModel;
    int ramSize;

   public:
    ComputingUnit(string processor = "amd", int ram = 8) {
        processorModel = processor;
        ramSize = ram;
    }

    ~ComputingUnit() {
        cout << "Computing unit turned off" << endl;
    }

    string getProcessorModel() const {
        return processorModel;
    }

    int getRamSize() const {
        return ramSize;
    }

    void setProcessorModel(string processor) {
        processorModel = processor;
    }

    void setRamSize(int ram) {
        ramSize = ram;
    }

    void processorStream() const {
        cout << "Decoding video stream using " << processorModel << " (" << ramSize << " GB RAM)" << endl;
    }
};

class Speaker {
   private:
    int wattage;
    string position;

   public:
    Speaker(int watt = 20, string pos = "Left") {
        wattage = watt;
        position = pos;
    }

    ~Speaker() {
        cout << position << " speaker turned off" << endl;
    }

    int getWattage() const {
        return wattage;
    }

    string getPosition() const {
        return position;
    }

    void setWattage(int watt) {
        wattage = watt;
    }

    void setPosition(int pos) {
        position = pos;
    }

    void emitSound() const {
        cout << "Boom! Sound coming from " << position << " speaker at " << wattage << " watts" << endl;
    }
};

class SmartTV : public DisplayUnit, public ComputingUnit {
   private:
    string brandName;
    Speaker sp[2];
    vector<MediaContent*> contentLibrary;

   public:
    SmartTV(string brand = "Samsung", float screen = 65, string res = "4K", string processor = "amd", int ram = 8, int watt = 20) : DisplayUnit(screen, res), ComputingUnit(processor, ram) {
        brandName = brand;
        sp[0] = Speaker(watt, "Left");
        sp[1] = Speaker(watt, "Right");
    }

    ~SmartTV() {
        cout << brandName << " TV turned off" << endl;
    }

    void watchContent(int index) const {
        if (index < 0 || index >= getContentCount()) {
            cout << "Invalid content index!" << endl;
            return;
        }

        cout << "- - - Starting " << contentLibrary[index]->getMediaType() << " on " << brandName << " TV - - -" << endl;
        contentLibrary[index]->play();
        showVisuals();
        processorStream();

        for (int i = 0; i < 2; i++) {
            sp[i].emitSound();
        }
    }

    int getContentCount() const {
        return contentLibrary.size();
    }

    void addToLibrary(MediaContent* content) {
        contentLibrary.push_back(content);
    }

    void browseLibrary() {
        cout << "Content Library:" << endl;
        for (auto content : contentLibrary) {
            cout << "- " << content->getMediaType() << ": " << content->getContentInfo() << endl;
        }
    }
};

class MediaContent {
   protected:
    string title;
    int duration;
    float fileSize;

   public:
    MediaContent(string title, int duration = 120, float fileSize = 1024.0f) {
        this->title = title;
        this->duration = duration;
        this->fileSize = fileSize;
    }

    virtual void play() = 0;
    virtual string getMediaType() = 0;

    virtual string getContentInfo() {
        return "Title: " + title + ", Duration: " + to_string(duration) + " mins, File Size: " + to_string(fileSize) + " MB";
    }
};

class Movie : public MediaContent {
   private:
    string director;
    bool hasHDR;

   public:
    Movie(string title, string director, int duration = 120, float fileSize = 2048.0f, bool hasHDR = true) : MediaContent(title, duration, fileSize) {
        this->director = director;
        this->hasHDR = hasHDR;
    }

    void play() {
        cout << "Playing movie: " << title << " directed by: " << director << endl;
    }

    string getMediaType() {
        return "Movie";
    }
};

class TVShow: public MediaContent {
    private:
    int seasonNumber;
    int episodeNumber;

    public:
    TVShow(string title, int season, int episode, int duration = 45, float fileSize = 512.0f) : MediaContent(title, duration, fileSize) {
        seasonNumber = season;
        episodeNumber = episode;
    }

    void play() {
        cout << "Playing TV Show: " << title << " (S" << seasonNumber << "E" << episodeNumber << ")" << endl; 
    }

    string getMediaType() {
        return "TV Show";
    }
};

int main() {
    SmartTV tv = SmartTV();

    // tv.watchMovie();
    return 0;
}