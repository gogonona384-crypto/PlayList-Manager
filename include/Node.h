#ifndef NODE_H
#define NODE_H

#include "MediaItem.h"

class Node {
private:
    MediaItem* item;
    Node* next;
    Node* prev;

public:
    explicit Node(MediaItem* mediaItem = nullptr);

    MediaItem* getItem() const;

    Node* getNext() const;
    Node* getPrev() const;

    void setNext(Node* node);
    void setPrev(Node* node);
};

#endif