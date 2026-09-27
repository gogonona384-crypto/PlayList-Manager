#include "Node.h"

Node::Node(MediaItem* mediaItem)
    : item(mediaItem), next(nullptr), prev(nullptr) {
}

MediaItem* Node::getItem() const {
    return item;
}

Node* Node::getNext() const {
    return next;
}

Node* Node::getPrev() const {
    return prev;
}

void Node::setNext(Node* node) {
    next = node;
}

void Node::setPrev(Node* node) {
    prev = node;
}