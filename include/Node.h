#ifndef NODE_H
#define NODE_H

#include "MediaItem.h"

struct Node {
    MediaItem* item;
    Node* next;
    Node* prev;

    Node(MediaItem* mediaItem) {
        item = mediaItem;
        next = nullptr;
        prev = nullptr;
    }
};

#endif