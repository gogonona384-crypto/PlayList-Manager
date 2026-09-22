#include "Podcast.h"

Podcast::Podcast(string t, string h, int d, int ep)
    : MediaItem(t, d), host(h), episodeNumber(ep) {}

void Podcast::play() {
    incrementPlayCount();
    cout << "[PODCAST] Playing " << title << " (Ep. " << episodeNumber << "), hosted by " << host << endl;
}

void Podcast::getInfo() const {
    cout << "[PODCAST] " << title << " | Host: " << host
         << " | Ep: " << episodeNumber << " | Duration: " << getFormattedDuration()
         << " | Plays: " << playCount << endl;
}

string Podcast::getHost() const { 
    return host; 
}

int Podcast::getEpisodeNumber() const { 
    return episodeNumber; 
}