#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class MediaItem {
protected:
    string title;
    int duration; 
    int playCount;

public:
    MediaItem(string t = "", int d = 0) : title(t), duration(d), playCount(0) {}
    
    virtual ~MediaItem() = default; 

    virtual void play() = 0;
    virtual void getInfo() const = 0;

    string getTitle() const { return title; }
    int getDuration() const { return duration; }
    int getPlayCount() const { return playCount; }
    void incrementPlayCount() { playCount++; }

    string getFormattedDuration() const {
        int mins = duration / 60;
        int secs = duration % 60;
        ostringstream oss;
        oss << setfill('0') << setw(2) << mins << ":" 
            << setfill('0') << setw(2) << secs;
        return oss.str();
    }

    bool operator<(const MediaItem& other) const {
        return this->title < other.title;
    }

    friend ostream& operator<<(ostream& os, const MediaItem& item)
     {
        os << "Title: " << item.title 
           << " | Duration: " << item.getFormattedDuration() 
           << " | Plays: " << item.playCount;
           item.getInfo();
        return os;
    }
};

#endif