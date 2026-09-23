#include "Playlist.h"

Playlist::Playlist() : head(nullptr), tail(nullptr), currentTrack(nullptr) {}

int Playlist::calculateDurationRecursive(Node* node) const {
    if (node == nullptr) return 0;
    return node->item->getDuration() + calculateDurationRecursive(node->next);
}

void Playlist::printBackwardsRecursive(Node* node, int index) const {
    if (node == nullptr) return;
    cout << index << ". " << node->item->getTitle() << endl;
    printBackwardsRecursive(node->prev, index - 1); 
}

void Playlist::addTrack(MediaItem* item) {
    Node* newNode = new Node(item);
    if (head == nullptr) {
        head = tail = currentTrack = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    cout << "[OK] Added to playlist." << endl;
}

void Playlist::removeTrack(int index) {
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

    if (head == nullptr) {
        tail = nullptr;
        currentTrack = nullptr;
    }

    cout << "[OK] Track removed successfully." << endl;
}

MediaItem* Playlist::playCurrent() {
    if (currentTrack && currentTrack->item) {
        cout << ">>> NOW PLAYING: " << currentTrack->item->getTitle() << endl;
        currentTrack->item->incrementPlayCount(); 
        currentTrack->item->play();
        return currentTrack->item; 
    } else {
        cout << "Playlist is empty!" << endl;
        return nullptr;
    }
}

MediaItem* Playlist::nextTrack() {
    if (currentTrack && currentTrack->next) {
        currentTrack = currentTrack->next;
        return playCurrent();
    } else {
        cout << "[!] You are on the last track." << endl;
        return nullptr;
    }
}

MediaItem* Playlist::prevTrack() {
    if (currentTrack && currentTrack->prev) {
        currentTrack = currentTrack->prev;
        return playCurrent();
    } else {
        cout << "[!] You are on the first track." << endl;
        return nullptr;
    }
}

void Playlist::printForwards() const {
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

void Playlist::printBackwards() const {
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

void Playlist::showTotalDuration() const {
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

Playlist::~Playlist() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current; 
        current = nextNode;
    }
}