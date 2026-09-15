#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include "Node.h"

using namespace std;

class Playlist {
private:
    Node* head;
    Node* tail;
    Node* currentTrack;

    int calculateDurationRecursive(Node* node) {
        if (node == nullptr) return 0;
        return node->item->getDuration() + calculateDurationRecursive(node->next);
    }

public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
        currentTrack = nullptr;
    }

    void addTrack(MediaItem* item) {
        Node* newNode = new Node(item);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            currentTrack = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void nextTrack() {
        if (currentTrack && currentTrack->next) {
            currentTrack = currentTrack->next;
            cout << "Switched to next track:\n";
            currentTrack->item->play();
        } else {
            cout << "Already at the end of the playlist!\n";
        }
    }

    void prevTrack() {
        if (currentTrack && currentTrack->prev) {
            currentTrack = currentTrack->prev;
            cout << "Switched to previous track:\n";
            currentTrack->item->play();
        } else {
            cout << "Already at the beginning of the playlist!\n";
        }
    }

    void printForwards() {
        cout << "\n=== Playlist (Forwards) ===\n";
        Node* temp = head;
        while (temp != nullptr) {
            temp->item->getInfo();
            temp = temp->next;
        }
    }

    void printBackwards() {
        cout << "\n=== Playlist (Backwards) ===\n";
        Node* temp = tail;
        while (temp != nullptr) {
            temp->item->getInfo();
            temp = temp->prev;
        }
    }

    int getTotalDuration() {
        return calculateDurationRecursive(head);
    }

    ~Playlist() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current->item; 
            delete current;       
            current = nextNode;
        }
    }
};

#endif