#ifndef PLAYQUEUE_H
#define PLAYQUEUE_H

#include "Node.h"

class PlayQueue {
private:
    Node* front;
    Node* rear;

public:
    PlayQueue();
    ~PlayQueue();

    PlayQueue(const PlayQueue&) = delete;
    PlayQueue& operator=(const PlayQueue&) = delete;

    void enqueue(MediaItem* item);
    MediaItem* playNext();

    void displayQueue() const;

    void removeItem(MediaItem* item);
    bool contains(MediaItem* item) const;

    bool isEmpty() const;
};

#endif