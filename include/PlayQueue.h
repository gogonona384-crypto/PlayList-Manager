#ifndef PLAYQUEUE_H
#define PLAYQUEUE_H

#include <iostream>
#include "Node.h"

using namespace std;

class PlayQueue {
private:
    Node* front;
    Node* rear;

public:
    PlayQueue();
    ~PlayQueue();

    void enqueue(MediaItem* item);
    void playNext();
    void displayQueue() const;
    
    bool isEmpty() const { return front == nullptr; }
};

#endif