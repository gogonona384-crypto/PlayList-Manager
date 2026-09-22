#ifndef HISTORYSTACK_H
#define HISTORYSTACK_H

#include <iostream>
#include "MediaItem.h"

class HistoryStack {
private:
    MediaItem* items[10]; 
    int topIndex = -1;       
    const int capacity = 10;

public:
    HistoryStack() { 
        topIndex = -1;
        for (int i = 0; i < capacity; i++) {
            items[i] = nullptr;
        }
    }

    void push(MediaItem* item) 
    {
      if (item == nullptr)
            return;
        if (topIndex < capacity - 1) {
            topIndex++;
            items[topIndex] = item;
        } else {
            for (int i = 0; i < capacity - 1; i++) {
                items[i] = items[i + 1];
            }
                items[capacity - 1] = item;
        }
    }

    MediaItem* pop() {
        if (topIndex >= 0) {
            MediaItem* item = items[topIndex];
            items[topIndex] = nullptr;
            topIndex--;
            return item;
        }
        return nullptr; 
    }

    MediaItem* top() const {
        if (topIndex >= 0) {
            return items[topIndex];
        }
        return nullptr; 
    }

    bool empty() const {
        return topIndex == -1;
    }

    void clear() {
        for (int i = 0; i <= topIndex; i++) {
            items[i] = nullptr;
        }
        topIndex = -1;
    }

    void displayHistory() const {
        if (empty()) {
            std::cout << "History is empty!" << std::endl;
            return;
        }
        std::cout << "Playback History (Most Recent First):" << std::endl;
        for (int i = topIndex; i >= 0; i--) {
            std::cout << (topIndex - i + 1) << ". " << items[i]->getTitle() << std::endl;
        }
    }

    ~HistoryStack() {
        clear();
    }
};

#endif