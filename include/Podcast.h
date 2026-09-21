#ifndef PODCAST_H
#define PODCAST_H

#include "MediaItem.h"

class Podcast : public MediaItem {
private:
    string host;
    int episodeNumber;

public:
    Podcast(string t = "", string h = "", int d = 0, int ep = 0)
        : MediaItem(t, d), host(h), episodeNumber(ep) {}

    void play() override {
        // Ziada: al-increment momken yet'amel hena aw fel-Queue/Playlist
        cout << "[PODCAST] " << title << " (Ep. " << episodeNumber << "), hosted by " << host << endl;
    }

    void getInfo() const override {
        cout << "[PODCAST] " << title << " | Host: " << host
             << " | Ep: " << episodeNumber << " | Duration: " << getFormattedDuration()
             << " | Plays: " << playCount << endl;
    }

    string getHost() const { return host; }
    int getEpisodeNumber() const { return episodeNumber; }
};

#endif