#ifndef SONG_H
#define SONG_H

#include "MediaItem.h"

class Song : public MediaItem
{
private:
    string artist;
    string genre;

public:
    Song(string t, string a, int d, string g)
        : MediaItem(t, d), artist(a), genre(g) {}

    void play() override
    {
        incrementPlayCount();
        cout << ">>> NOW PLAYING: " << title << "\n"
             << artist << " (" << duration << ")\n"
             << "[SONG] streaming audio...\n";
    }
    void getInfo() const override
    {
        cout << "[SONG] " << title << " | Artist: " << artist
             << " | Duration: " << duration << " | Genre: " << genre
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