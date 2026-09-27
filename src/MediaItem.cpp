#include "MediaItem.h"

#include <iomanip>
#include <sstream>

MediaItem::MediaItem(string t, int d)
    : title(t), duration(d < 0 ? 0 : d), playCount(0) {
}

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
    int minutes = duration / 60;
    int seconds = duration % 60;

    ostringstream out;

    out << setfill('0')
        << setw(2) << minutes
        << ":"
        << setw(2) << seconds;

    return out.str();
}

bool MediaItem::operator<(const MediaItem& other) const {
    return title < other.title;
}

string MediaItem::getArtist() const {
    return "";
}

string MediaItem::getGenre() const {
    return "";
}

void MediaItem::displayInfo() const {
    cout << *this << endl;
}

ostream& operator<<(ostream& os, const MediaItem& item) {
    os << item.title
       << " | "
       << item.getFormattedDuration()
       << " | Plays: "
       << item.playCount;

    return os;
}