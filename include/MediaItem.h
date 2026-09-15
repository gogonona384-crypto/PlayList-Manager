#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <string>
#include <iostream>
using namespace std;

class MediaItem {
protected:
    string title;
    int duration; 
    int playCount;

public:
    MediaItem(string t = "", int d = 0) : title(t), duration(d), playCount(0) {}
    virtual ~MediaItem() {}

    // Pure Virtual Function
    virtual void play() = 0;
    virtual void getInfo() const = 0;

    string getTitle() const { return title; }
    int getDuration() const { return duration; }
    int getPlayCount() const { return playCount; }
    void incrementPlayCount() { playCount++; }
};

#endif