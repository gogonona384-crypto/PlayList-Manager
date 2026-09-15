#ifndef PODCAST_H
#define PODCAST_H

#include "MediaItem.h"

class Podcast : public MediaItem {
private:
    string host;
    int episodeNumber;

public:
    Podcast(string t, string h, int d, int ep)
        : MediaItem(t, d), host(h), episodeNumber(ep) {}

    void play() override {
        incrementPlayCount();
        cout << ">>> NOW PLAYING: " << title << " (" << duration << ")\n"
             << "[PODCAST] episode " << episodeNumber << ", hosted by " << host << "\n";
    }

    void getInfo() const override {
        cout << "[PODCAST] " << title << " | Host: " << host
             << " | Ep: " << episodeNumber << " | Duration: " << duration
             << " | Plays: " << playCount << endl;
    }

    string getHost() const { return host; }
    int getEpisodeNumber() const { return episodeNumber; }
};

#endif