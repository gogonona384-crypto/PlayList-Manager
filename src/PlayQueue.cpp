#include "PlayQueue.h"

#include <iostream>

PlayQueue::PlayQueue()
    : front(nullptr), rear(nullptr) {
}

void PlayQueue::enqueue(MediaItem* item) {
    if (item == nullptr) {
        cout << "[X] Invalid track." << endl;
        return;
    }

    Node* newNode = new Node(item);

    if (front == nullptr) {
        front = rear = newNode;
    }
    else {
        newNode->setPrev(rear);
        rear->setNext(newNode);
        rear = newNode;
    }

    cout << "[OK] "
         << item->getTitle()
         << " added to the queue."
         << endl;
}

MediaItem* PlayQueue::playNext() {
    if (front == nullptr) {
        cout << "[X] Nothing in the queue." << endl;
        return nullptr;
    }

    Node* temp = front;

    MediaItem* item = temp->getItem();

    cout << "\n>>> NOW PLAYING: "
         << item->getTitle();

    string creator = item->getCreator();

    if (!creator.empty()) {
        cout << " - " << creator;
    }

    cout << " ("
         << item->getFormattedDuration()
         << ")"
         << endl;

    item->play();

    front = temp->getNext();

    if (front == nullptr) {
        rear = nullptr;
        cout << "Queue is now empty." << endl;
    }
    else {
        front->setPrev(nullptr);

        int remaining = 0;

        Node* current = front;

        while (current != nullptr) {
            remaining++;
            current = current->getNext();
        }

        cout << remaining
             << (remaining == 1
                     ? " track left in the queue."
                     : " tracks left in the queue.")
             << endl;
    }

    delete temp;

    return item;
}

void PlayQueue::displayQueue() const {
    if (front == nullptr) {
        cout << "[X] Nothing in the queue." << endl;
        return;
    }

    cout << "\nUP NEXT" << endl;

    Node* current = front;
    int index = 1;

    while (current != nullptr) {
        cout << index++
             << ". "
             << current->getItem()->getTitle()
             << endl;

        current = current->getNext();
    }
}

void PlayQueue::removeItem(MediaItem* item) {
    if (item == nullptr) {
        return;
    }

    Node* current = front;

    while (current != nullptr) {
        Node* next = current->getNext();

        if (current->getItem() == item) {

            Node* prev = current->getPrev();

            if (prev != nullptr) {
                prev->setNext(next);
            }
            else {
                front = next;
            }

            if (next != nullptr) {
                next->setPrev(prev);
            }
            else {
                rear = prev;
            }

            delete current;
        }

        current = next;
    }
}

bool PlayQueue::contains(MediaItem* item) const {
    if (item == nullptr) {
        return false;
    }

    Node* current = front;

    while (current != nullptr) {
        if (current->getItem() == item) {
            return true;
        }

        current = current->getNext();
    }

    return false;
}

bool PlayQueue::isEmpty() const {
    return front == nullptr;
}

PlayQueue::~PlayQueue() {
    while (front != nullptr) {
        Node* temp = front;

        front = front->getNext();

        delete temp;
    }

    rear = nullptr;
}