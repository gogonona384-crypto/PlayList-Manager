#include <iostream>
#include <iomanip>
#include "MediaItem.h"

MediaItem::MediaItem(string t, int d) : title(t), duration(d), playCount(0) {}

string MediaItem::getTitle() const { 
    return title; 
}

int MediaItem::getDuration() const { 
    return duration; 
}

int MediaItem::getPlayCount() const { 
    return playCount; 
}

void MediaItem::incrementPlayCount() { 
    playCount++; 
}

string MediaItem::getFormattedDuration() const {
    int mins = duration / 60;
    int secs = duration % 60;
    ostringstream oss;
    oss << setfill('0') << setw(2) << mins << ":" 
        << setfill('0') << setw(2) << secs;
    return oss.str();
}

bool MediaItem::operator<(const MediaItem& other) const {
    return this->title < other.title;
}

ostream& operator<<(ostream& os, const MediaItem& item) {
    os << item.getTitle() << " (" << item.getFormattedDuration() << ") - Plays: " << item.getPlayCount();
    return os;
}