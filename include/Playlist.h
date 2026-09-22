#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <iomanip>
#include "Node.h"

using namespace std;

class Playlist {
private:
    Node* head;
    Node* tail;
    Node* currentTrack;

    int calculateDurationRecursive(Node* node) const;
    void printBackwardsRecursive(Node* node, int index) const;

public:
    Playlist();
    ~Playlist();

    void addTrack(MediaItem* item);
    void removeTrack(int index);
    
    MediaItem* playCurrent();
    MediaItem* nextTrack();
    MediaItem* prevTrack();

    void printForwards() const;
    void printBackwards() const;
    void showTotalDuration() const;
};

#endif