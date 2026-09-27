#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <iostream>
#include <string>

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

    virtual string getType() const = 0;
    virtual string getCreator() const = 0;

    string getTitle() const;
    int getDuration() const;
    int getPlayCount() const;

    void incrementPlayCount();

    string getFormattedDuration() const;

    bool operator<(const MediaItem& other) const;

    virtual string getArtist() const;
    virtual string getGenre() const;

    virtual void displayInfo() const;

    friend ostream& operator<<(ostream& os, const MediaItem& item);
};

#endif