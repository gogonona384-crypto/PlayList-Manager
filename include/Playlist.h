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

    // Recursive function to total duration
    int calculateDurationRecursive(Node* node) 
    {
        if (node == nullptr) return 0;
        return node->item->getDuration() + calculateDurationRecursive(node->next);
    }

    // Recursive function to print backwards
    void printBackwardsRecursive(Node* node, int index) 
    {
        if (node == nullptr) return;
        cout << index << ". " << node->item->getTitle() << endl;
        printBackwardsRecursive(node->prev, index - 1); 
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
        cout << "[OK] Added to playlist." << endl;
    }

    void removeTrack(int index) {
        if (head == nullptr || index < 1) {
            cout << "Invalid index or playlist is empty!" << endl;
            return;
        }

        Node* temp = head;
        int count = 1;

        while (temp != nullptr && count < index) {
            temp = temp->next;
            count++;
        }

        if (temp == nullptr) {
            cout << "Invalid index!" << endl;
            return;
        }

        if (temp == currentTrack) {
            currentTrack = (temp->next) ? temp->next : temp->prev;
        }

        if (temp == head) head = head->next;
        if (temp == tail) tail = tail->prev;

        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;

        delete temp;
        cout << "[OK] Track removed successfully." << endl;
    }

    void playCurrent() {
        if (currentTrack) {
            cout << "> NOW PLAYING: ";
            currentTrack->item->play();
            currentTrack->item->incrementPlayCount();
        } else {
            cout << "Playlist is empty!" << endl;
        }
    }

    void nextTrack() {
        if (currentTrack && currentTrack->next) {
            currentTrack = currentTrack->next;
            playCurrent();
        } else {
            cout << "[!] You are on the last track." << endl;
        }
    }

    void prevTrack() {
        if (currentTrack && currentTrack->prev) {
            currentTrack = currentTrack->prev;
            playCurrent();
        } else {
            cout << "[!] You are on the first track." << endl;
        }
    }

    void printForwards() {
        if (head == nullptr) {
            cout << "Playlist is empty!" << endl;
            return;
        }
        Node* temp = head;
        int index = 1;
        while (temp != nullptr) {
            cout << index++ << ". " << temp->item->getTitle() << endl;
            temp = temp->next;
        }
    }

    void printBackwards() {
        if (tail == nullptr) {
            cout << "Playlist is empty!" << endl;
            return;
        }
        
        int totalTracks = 0;
        Node* temp = head;
        while (temp) { 
            totalTracks++; 
            temp = temp->next; 
        }
        
        printBackwardsRecursive(tail, totalTracks); 
    }

    void showTotalDuration() {
        if (head == nullptr) {
            cout << "Playlist is empty!" << endl;
            return;
        }

        int totalSeconds = calculateDurationRecursive(head);
        int mins = totalSeconds / 60;
        int secs = totalSeconds % 60;

        int trackCount = 0;
        Node* temp = head;
        while (temp) { trackCount++; temp = temp->next; }

        cout << "Total: " << setfill('0') << setw(2) << mins << ":" 
             << setfill('0') << setw(2) << secs 
             << " over " << trackCount << " tracks [recursive sum]" << endl;
    }

    ~Playlist() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current; 
            current = nextNode;
        }
    }
};

#endif