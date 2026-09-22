#include "Song.h"

Song::Song(string t, string a, int d, string g)
    : MediaItem(t, d), artist(a), genre(g) {}

void Song::play() {
    incrementPlayCount();
    cout << "[SONG] " << title << " by " << artist << " - streaming audio..." << endl;
}

void Song::getInfo() const {
    cout << "[SONG] " << title << " | Artist: " << artist
         << " | Duration: " << getFormattedDuration() << " | Genre: " << genre
         << " | Plays: " << playCount << endl;
}

string Song::getArtist() const {
    return artist;
}

string Song::getGenre() const {
    return genre;
}