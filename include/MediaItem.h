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
    MediaItem(string t = "", int d = 0);
    virtual ~MediaItem() = default; 

    virtual void play() = 0;
    virtual void getInfo() const = 0;
    virtual void displayInfo() const {
        cout << *this << endl;
    }

    string getTitle() const;
    int getDuration() const;
    int getPlayCount() const;
    void incrementPlayCount();

    virtual string getArtist() const { return ""; }
    virtual string getGenre() const { return ""; }

    string getFormattedDuration() const;
    bool operator<(const MediaItem& other) const;

    friend ostream& operator<<(ostream& os, const MediaItem& item);
};

#endif