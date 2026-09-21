#ifndef SONG_H
#define SONG_H

#include "MediaItem.h"

class Song : public MediaItem
{
private:
    string artist;
    string genre;

public:
    Song(string t = "", string a = "", int d = 0, string g = "")
        : MediaItem(t, d), artist(a), genre(g) {}

    void play() override
    {
        cout << "[SONG] " << title << " by " << artist << " - streaming audio..." << endl;
    }

    void getInfo() const override
    {
        cout << "[SONG] " << title << " | Artist: " << artist
             << " | Duration: " << getFormattedDuration() << " | Genre: " << genre
             << " | Plays: " << playCount << endl;
    }

    string getArtist() const
    {
        return artist;
    }

    string getGenre() const
    {
        return genre;
    }
};

#endif