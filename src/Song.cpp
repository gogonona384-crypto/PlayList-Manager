#include "Song.h"

#include <iostream>

Song::Song(string t, string a, int d, string g)
    : MediaItem(t, d), artist(a), genre(g) {
}

void Song::play() {
    incrementPlayCount();

    cout << "[SONG] streaming audio." << endl;
}

void Song::getInfo() const {
    cout << "[SONG] "
         << title
         << " | Artist: "
         << artist
         << " | Genre: "
         << genre
         << " | Duration: "
         << getFormattedDuration()
         << " | Plays: "
         << playCount
         << endl;
}

string Song::getType() const {
    return "SONG";
}

string Song::getCreator() const {
    return artist;
}

string Song::getArtist() const {
    return artist;
}

string Song::getGenre() const {
    return genre;
}