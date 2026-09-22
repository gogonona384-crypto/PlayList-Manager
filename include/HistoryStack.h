#ifndef HISTORYSTACK_H
#define HISTORYSTACK_H

#include <iostream>
#include "MediaItem.h"

class HistoryStack {
private:
    static constexpr int CAPACITY = 10;
    MediaItem* items[CAPACITY];
    int topIndex;

public:
    HistoryStack();
    ~HistoryStack();

    void push(MediaItem* item);
    MediaItem* pop();
    MediaItem* top() const;

    bool empty() const;
    bool full() const;
    int size() const;
    void clear();

    void displayHistory() const;
};

#endif