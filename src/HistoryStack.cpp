#include "HistoryStack.h"

HistoryStack::HistoryStack() : topIndex(-1) {
    for (int i = 0; i < CAPACITY; i++) {
        items[i] = nullptr;
    }
}

HistoryStack::~HistoryStack() {
    clear();
}

void HistoryStack::push(MediaItem* item) {
    if (item == nullptr) return;

    if (topIndex < CAPACITY - 1) {
        items[++topIndex] = item;
    } else {
        for (int i = 0; i < CAPACITY - 1; i++) {
            items[i] = items[i + 1];
        }
        items[CAPACITY - 1] = item;
    }
}

MediaItem* HistoryStack::pop() {
    if (topIndex < 0) return nullptr;
    MediaItem* item = items[topIndex];
    items[topIndex] = nullptr;
    topIndex--;
    return item;
}

MediaItem* HistoryStack::top() const {
    return (topIndex >= 0) ? items[topIndex] : nullptr;
}

bool HistoryStack::empty() const { return topIndex == -1; }
bool HistoryStack::full() const  { return topIndex == CAPACITY - 1; }
int  HistoryStack::size() const  { return topIndex + 1; }

void HistoryStack::clear() {
    for (int i = 0; i <= topIndex; i++) {
        items[i] = nullptr;
    }
    topIndex = -1;
}

void HistoryStack::displayHistory() const {
    if (empty()) {
        std::cout << "No play history yet.\n";
        return;
    }
    std::cout << "--- PLAY HISTORY (most recent first) ---\n";
    int display = 1;
    for (int i = topIndex; i >= 0; i--) {
        std::cout << display++ << ". " << items[i]->getTitle() << "\n";
    }
}