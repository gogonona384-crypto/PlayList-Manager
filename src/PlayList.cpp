#include "Playlist.h"

#include <iomanip>
#include <iostream>

Playlist::Playlist()
    : head(nullptr), tail(nullptr), currentTrack(nullptr) {
}

int Playlist::calculateDurationRecursive(Node* node) const {
    if (node == nullptr) {
        return 0;
    }

    return node->getItem()->getDuration()
         + calculateDurationRecursive(node->getNext());
}

void Playlist::printBackwardsRecursive(Node* node, int index) const {
    if (node == nullptr) {
        return;
    }

    cout << index
         << ". "
         << node->getItem()->getTitle()
         << endl;

    printBackwardsRecursive(node->getPrev(), index - 1);
}

void Playlist::addTrack(MediaItem* item) {
    if (item == nullptr) {
        cout << "[X] Invalid track." << endl;
        return;
    }

    Node* newNode = new Node(item);

    if (head == nullptr) {
        head = tail = currentTrack = newNode;
    }
    else {
        newNode->setPrev(tail);
        tail->setNext(newNode);
        tail = newNode;
    }

    cout << "[OK] "
         << item->getTitle()
         << " added to playlist."
         << endl;
}

void Playlist::removeTrack(int index) {
    if (head == nullptr) {
        cout << "[X] Playlist is empty." << endl;
        return;
    }

    if (index < 1) {
        cout << "[X] Invalid index." << endl;
        return;
    }

    Node* target = head;
    int currentIndex = 1;

    while (target != nullptr && currentIndex < index) {
        target = target->getNext();
        currentIndex++;
    }

    if (target == nullptr) {
        cout << "[X] Invalid index." << endl;
        return;
    }

    Node* prev = target->getPrev();
    Node* next = target->getNext();

    if (target == currentTrack) {
        if (next != nullptr) {
            currentTrack = next;
        }
        else {
            currentTrack = prev;
        }
    }

    if (prev != nullptr) {
        prev->setNext(next);
    }
    else {
        head = next;
    }

    if (next != nullptr) {
        next->setPrev(prev);
    }
    else {
        tail = prev;
    }

    delete target;

    if (head == nullptr) {
        tail = nullptr;
        currentTrack = nullptr;
    }

    cout << "[OK] Track removed successfully." << endl;
}

void Playlist::removeItem(MediaItem* item) {
    if (item == nullptr) {
        return;
    }

    Node* current = head;

    while (current != nullptr) {
        Node* next = current->getNext();

        if (current->getItem() == item) {

            Node* prev = current->getPrev();

            if (current == currentTrack) {
                if (next != nullptr) {
                    currentTrack = next;
                }
                else {
                    currentTrack = prev;
                }
            }

            if (prev != nullptr) {
                prev->setNext(next);
            }
            else {
                head = next;
            }

            if (next != nullptr) {
                next->setPrev(prev);
            }
            else {
                tail = prev;
            }

            delete current;
        }

        current = next;
    }

    if (head == nullptr) {
        head = tail = currentTrack = nullptr;
    }
}

bool Playlist::contains(MediaItem* item) const {
    if (item == nullptr) {
        return false;
    }

    Node* current = head;

    while (current != nullptr) {
        if (current->getItem() == item) {
            return true;
        }

        current = current->getNext();
    }

    return false;
}

MediaItem* Playlist::playCurrent() {
    if (currentTrack == nullptr ||
        currentTrack->getItem() == nullptr) {

        cout << "[X] Playlist is empty." << endl;
        return nullptr;
    }

    MediaItem* item = currentTrack->getItem();

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

    return item;
}

MediaItem* Playlist::nextTrack() {
    if (currentTrack == nullptr) {
        cout << "[X] Playlist is empty." << endl;
        return nullptr;
    }

    if (currentTrack->getNext() == nullptr) {
        cout << "[!] You are on the last track." << endl;
        return nullptr;
    }

    currentTrack = currentTrack->getNext();

    return playCurrent();
}

MediaItem* Playlist::prevTrack() {
    if (currentTrack == nullptr) {
        cout << "[X] Playlist is empty." << endl;
        return nullptr;
    }

    if (currentTrack->getPrev() == nullptr) {
        cout << "[!] You are on the first track." << endl;
        return nullptr;
    }

    currentTrack = currentTrack->getPrev();

    return playCurrent();
}

void Playlist::printForwards() const {
    if (head == nullptr) {
        cout << "Playlist is empty." << endl;
        return;
    }

    cout << "\nPLAYLIST FORWARDS" << endl;

    Node* current = head;
    int index = 1;

    while (current != nullptr) {
        cout << index++
             << ". "
             << current->getItem()->getTitle()
             << endl;

        current = current->getNext();
    }
}

void Playlist::printBackwards() const {
    if (tail == nullptr) {
        cout << "Playlist is empty." << endl;
        return;
    }

    int totalTracks = 0;

    Node* current = head;

    while (current != nullptr) {
        totalTracks++;
        current = current->getNext();
    }

    cout << "\nPLAYLIST BACKWARDS" << endl;

    printBackwardsRecursive(tail, totalTracks);

    cout << "[recursive, uses prev pointers]" << endl;
}

void Playlist::showTotalDuration() const {
    if (head == nullptr) {
        cout << "Playlist is empty." << endl;
        return;
    }

    int totalSeconds = calculateDurationRecursive(head);

    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    int trackCount = 0;

    Node* current = head;

    while (current != nullptr) {
        trackCount++;
        current = current->getNext();
    }

    cout << "Total: "
         << setfill('0')
         << setw(2)
         << minutes
         << ":"
         << setw(2)
         << seconds
         << " over "
         << trackCount
         << (trackCount == 1 ? " track" : " tracks")
         << " [recursive sum]"
         << endl;

    cout << setfill(' ');
}

Playlist::~Playlist() {
    Node* current = head;

    while (current != nullptr) {
        Node* next = current->getNext();

        delete current;

        current = next;
    }

    head = nullptr;
    tail = nullptr;
    currentTrack = nullptr;
}