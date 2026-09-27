#ifndef HISTORYSTACK_H
#define HISTORYSTACK_H

#include "MediaItem.h"

class HistoryStack {
private:
    struct HistoryNode {
        MediaItem* item;
        HistoryNode* next;

        HistoryNode(MediaItem* media, HistoryNode* nextNode = nullptr)
            : item(media), next(nextNode) {}
    };

    HistoryNode* top;
    int count;

    static const int MAX_HISTORY = 10;

    void clear();

public:
    HistoryStack();
    ~HistoryStack();

    void push(MediaItem* item);
    void removeItem(MediaItem* item);

    void displayHistory() const;
};

#endif