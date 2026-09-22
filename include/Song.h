#ifndef SONG_H
#define SONG_H

#include "MediaItem.h"

class Song : public MediaItem {
private:
    string artist;
    string genre;

public:
    Song(string t = "", string a = "", int d = 0, string g = "");

    void play() override;
    void getInfo() const override;

    string getArtist() const;
    string getGenre() const;
};

#endif