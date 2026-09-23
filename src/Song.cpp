#include "Song.h"

Song::Song(string t, string a, int d, string g)
    : MediaItem(t, d), artist(a), genre(g) {}

void Song::play() {
    incrementPlayCount();
    cout << artist << " (" << getFormattedDuration() << ")" << endl;
    cout << "[SONG] streaming audio..." << endl;
}

void Song::getInfo() const {
    cout << "[SONG] " << title << " | Artist: " << artist
         << " | Genre: " << genre << " | Duration: " << getFormattedDuration()
         << " | Plays: " << playCount << endl;
}

string Song::getArtist() const {
    return artist;
}

string Song::getGenre() const {
    return genre;
}