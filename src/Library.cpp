#include "Library.h"
#include <iostream>
#include <algorithm>

Library::Library(int initialCapacity) {
    capacity = initialCapacity;
    count = 0;
    items = new MediaItem*[capacity];

    historyCapacity = 10;
    historyCount = 0;
    history = new MediaItem*[historyCapacity];
}

Library::~Library() {
    for (int i = 0; i < count; i++) {
        delete items[i];
    }
    delete[] items;
    delete[] history;
}

void Library::resize() {
    capacity *= 2;
    MediaItem** newItems = new MediaItem*[capacity];
    for (int i = 0; i < count; i++) {
        newItems[i] = items[i];
    }
    delete[] items;
    items = newItems;
}

void Library::addTrack(MediaItem* item) {
    if (count == capacity) {
        resize();
    }
    items[count++] = item;
    std::cout << "[OK] Added. Library has " << count << " items.\n";
}

void Library::viewALL() const {
    if (count == 0) {
        std::cout << "Library is empty.\n";
        return;
    }
    std::cout << "ID\tTYPE\tTITLE\t\tPLAYS\n";
    for (int i = 0; i < count; i++) {
        std::cout << (i + 1) << "\t";
        items[i]->getInfo();
    }
}

void Library::deleteTrack(int index) {
    if (index < 0 || index >= count) {
        std::cout << "[X] Invalid index!\n";
        return;
    }
    delete items[index];
    for (int i = index; i < count - 1; i++) {
        items[i] = items[i + 1];
    }
    count--;
    std::cout << "[OK] Deleted successfully.\n";
}

MediaItem* Library::getTrack(int index) const {
    if (index >= 0 && index < count) return items[index];
    return nullptr;
}

int Library::getCount() const {
    return count;
}

void Library::binarySearchTitle(const std::string& title) const {
    int low = 0, high = count - 1;
    int comparisons = 0;
    bool found = false;

    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;
        if (items[mid]->getTitle() == title) {
            std::cout << "Found in " << comparisons << " comparisons\n";
            items[mid]->getInfo();
            found = true;
            break;
        }
        if (items[mid]->getTitle() < title) low = mid + 1;
        else high = mid - 1;
    }

    if (!found) {
        std::cout << "Not found. Comparisons made: " << comparisons << "\n";
    }
}

void Library::filterLinear(const std::string& query) const {
    int matches = 0;
    for (int i = 0; i < count; i++) {
        if (items[i]->getTitle().find(query) != std::string::npos) {
            items[i]->getInfo();
            matches++;
        }
    }
    std::cout << matches << " matches found.\n";
}

void Library::sortLibrary(int option) {
    int comparisons = 0;
    for (int i = 0; i < count - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < count; j++) {
            comparisons++;
            bool condition = false;
            if (option == 1) condition = items[j]->getTitle() < items[minIdx]->getTitle();
            else if (option == 2) condition = items[j]->getDuration() < items[minIdx]->getDuration();
            else if (option == 3) condition = items[j]->getPlayCount() > items[minIdx]->getPlayCount();

            if (condition) minIdx = j;
        }
        if (minIdx != i) {
            std::swap(items[i], items[minIdx]);
        }
    }
    std::cout << "Sorted in " << comparisons << " comparisons.\n";
}

void Library::showStats() const {
    double totalDuration = 0;
    for (int i = 0; i < count; i++) {
        totalDuration += items[i]->getDuration();
    }
    std::cout << "Library total: " << count << " items, Total Duration: " << totalDuration << "s\n";
}

void Library::addToHistory(MediaItem* item) {
    if (historyCount < historyCapacity) {
        history[historyCount++] = item;
    }
}

void Library::viewHistory() const {
    std::cout << "--- HISTORY ---\n";
    for (int i = historyCount - 1; i >= 0; i--) {
        std::cout << history[i]->getTitle() << "\n";
    }
}