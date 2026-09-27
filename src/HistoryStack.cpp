#include "HistoryStack.h"

#include <iostream>

HistoryStack::HistoryStack()
    : top(nullptr), count(0) {
}

void HistoryStack::clear() {
    while (top != nullptr) {
        HistoryNode* temp = top;

        top = top->next;

        delete temp;
    }

    count = 0;
}

HistoryStack::~HistoryStack() {
    clear();
}

void HistoryStack::push(MediaItem* item) {
    if (item == nullptr) {
        return;
    }

    // Keep the most recent occurrence only.
    removeItem(item);

    top = new HistoryNode(item, top);

    count++;

    if (count > MAX_HISTORY) {

        HistoryNode* current = top;

        while (current->next != nullptr &&
               current->next->next != nullptr) {

            current = current->next;
        }

        if (current->next != nullptr) {
            delete current->next;

            current->next = nullptr;

            count--;
        }
    }
}

void HistoryStack::removeItem(MediaItem* item) {
    if (item == nullptr) {
        return;
    }

    HistoryNode* current = top;
    HistoryNode* previous = nullptr;

    while (current != nullptr) {

        if (current->item == item) {

            HistoryNode* toDelete = current;

            current = current->next;

            if (previous == nullptr) {
                top = current;
            }
            else {
                previous->next = current;
            }

            delete toDelete;

            count--;
        }
        else {
            previous = current;
            current = current->next;
        }
    }
}

void HistoryStack::displayHistory() const {
    cout << "\n---------- PLAY HISTORY (last 10) ----------\n";

    if (top == nullptr) {
        cout << "History is empty." << endl;
        return;
    }

    const HistoryNode* current = top;

    int index = 1;

    while (current != nullptr) {

        cout << index++
             << ". "
             << current->item->getTitle()
             << " - "
             << current->item->getCreator()
             << endl;

        current = current->next;
    }
}