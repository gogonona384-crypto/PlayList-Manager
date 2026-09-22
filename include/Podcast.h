#ifndef PODCAST_H
#define PODCAST_H

#include "MediaItem.h"

class Podcast : public MediaItem {
private:
    string host;
    int episodeNumber;

public:
    Podcast(string t = "", string h = "", int d = 0, int ep = 0);

    void play() override;
    void getInfo() const override;

    string getHost() const;
    int getEpisodeNumber() const;
};

#endif