#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Node.h"

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

    Playlist(const Playlist&) = delete;
    Playlist& operator=(const Playlist&) = delete;

    void addTrack(MediaItem* item);
    void removeTrack(int index);

    void removeItem(MediaItem* item);
    bool contains(MediaItem* item) const;

    MediaItem* playCurrent();
    MediaItem* nextTrack();
    MediaItem* prevTrack();

    void printForwards() const;
    void printBackwards() const;

    void showTotalDuration() const;
};

#endif