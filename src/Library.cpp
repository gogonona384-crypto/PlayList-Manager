#include "Library.h"

#include <iomanip>
#include <iostream>

namespace {

int compareText(const string& left, const string& right) {
    if (left < right) {
        return -1;
    }

    if (left > right) {
        return 1;
    }

    return 0;
}

}

Library::Library(int initialCapacity)
    : items(nullptr),
      capacity(initialCapacity < 1 ? 1 : initialCapacity),
      count(0),
      playHistory() {

    items = new MediaItem*[capacity];
}

Library::~Library() {

    for (int i = 0; i < count; i++) {
        delete items[i];
    }

    delete[] items;
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

    if (item == nullptr) {
        cout << "[X] Cannot add an empty item." << endl;
        return;
    }

    if (count == capacity) {
        resize();
    }

    items[count] = item;
    count++;

    cout << "[OK] Added. Library has "
         << count
         << " items."
         << endl;
}

void Library::printTableHeader() const {

    cout << left
         << setw(5) << "ID"
         << setw(10) << "TYPE"
         << setw(24) << "TITLE"
         << setw(20) << "BY"
         << setw(10) << "LENGTH"
         << "PLAYS"
         << endl;

    cout << "--------------------------------------------------------------"
         << endl;
}

void Library::printRow(int index) const {

    const MediaItem* item = items[index];

    cout << left
         << setw(5) << index + 1
         << setw(10) << item->getType()
         << setw(24) << item->getTitle()
         << setw(20) << item->getCreator()
         << setw(10) << item->getFormattedDuration()
         << item->getPlayCount()
         << endl;
}

void Library::viewALL() const {

    if (count == 0) {
        cout << "Library is empty." << endl;
        return;
    }

    cout << "\n------------- LIBRARY -------------------"
         << endl;

    printTableHeader();

    for (int i = 0; i < count; i++) {
        printRow(i);
    }
}

void Library::deleteTrack(int index) {

    if (index < 0 || index >= count) {
        cout << "[X] Invalid track ID." << endl;
        return;
    }

    MediaItem* deletedItem = items[index];

    // Remove it from the history before deleting the object.
    playHistory.removeItem(deletedItem);

    delete deletedItem;

    for (int i = index; i < count - 1; i++) {
        items[i] = items[i + 1];
    }

    count--;

    cout << "[OK] Deleted successfully. Library has "
         << count
         << " items."
         << endl;
}

MediaItem* Library::getTrack(int index) const {

    if (index < 0 || index >= count) {
        return nullptr;
    }

    return items[index];
}

int Library::getCount() const {
    return count;
}

bool Library::isTitleSorted() const {

    for (int i = 1; i < count; i++) {

        if (items[i]->getTitle() <
            items[i - 1]->getTitle()) {

            return false;
        }
    }

    return true;
}

void Library::sortByTitleInternal() const {

    for (int i = 0; i < count - 1; i++) {

        int minIndex = i;

        for (int j = i + 1; j < count; j++) {

            if (*items[j] < *items[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {

            MediaItem* temp = items[i];

            items[i] = items[minIndex];

            items[minIndex] = temp;
        }
    }
}

void Library::binarySearchTitle(const string& title) {

    if (count == 0) {
        cout << "Library is empty." << endl;
        return;
    }

    // Binary search requires the array to be sorted by title.
    if (!isTitleSorted()) {
        sortByTitleInternal();
    }

    int low = 0;
    int high = count - 1;

    int comparisons = 0;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        comparisons++;

        int cmp =
            compareText(items[mid]->getTitle(), title);

        if (cmp == 0) {

            cout << "Found in "
                 << comparisons
                 << " comparisons [binary search]"
                 << endl;

            printTableHeader();
            printRow(mid);

            return;
        }

        if (cmp < 0) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    cout << "Not found in "
         << comparisons
         << " comparisons [binary search]"
         << endl;
}

void Library::filterLinear(const string& query) const {

    int matches = 0;

    for (int i = 0; i < count; i++) {

        if (items[i]->getArtist().find(query) != string::npos ||
            items[i]->getGenre().find(query) != string::npos) {

            matches++;
        }
    }

    cout << matches
         << " matches [linear search]"
         << endl;

    if (matches == 0) {
        return;
    }

    cout << left
         << setw(5) << "ID"
         << setw(24) << "TITLE"
         << "BY"
         << endl;

    cout << "---------------------------------------------"
         << endl;

    for (int i = 0; i < count; i++) {

        if (items[i]->getArtist().find(query) != string::npos ||
            items[i]->getGenre().find(query) != string::npos) {

            cout << left
                 << setw(5) << i + 1
                 << setw(24) << items[i]->getTitle()
                 << items[i]->getCreator()
                 << endl;
        }
    }
}

void Library::sortLibrary(int option) {

    if (count < 2) {
        cout << "Not enough items to sort." << endl;
        return;
    }

    if (option < 1 || option > 3) {
        cout << "[X] Invalid sort option." << endl;
        return;
    }

    int comparisons = 0;

    // Selection Sort
    for (int i = 0; i < count - 1; i++) {

        int selected = i;

        for (int j = i + 1; j < count; j++) {

            comparisons++;

            bool shouldSelect = false;

            if (option == 1) {

                shouldSelect =
                    *items[j] < *items[selected];
            }
            else if (option == 2) {

                shouldSelect =
                    items[j]->getDuration() <
                    items[selected]->getDuration();
            }
            else {

                shouldSelect =
                    items[j]->getPlayCount() >
                    items[selected]->getPlayCount();
            }

            if (shouldSelect) {
                selected = j;
            }
        }

        if (selected != i) {

            MediaItem* temp = items[i];

            items[i] = items[selected];

            items[selected] = temp;
        }
    }

    cout << "\nID  TITLE                    LENGTH    PLAYS"
         << endl;

    cout << "---------------------------------------------"
         << endl;

    for (int i = 0; i < count; i++) {

        cout << left
             << setw(4) << i + 1
             << setw(25) << items[i]->getTitle()
             << setw(10) << items[i]->getFormattedDuration()
             << items[i]->getPlayCount()
             << endl;
    }

    cout << "Sorted in "
         << comparisons
         << " comparisons [selection sort]"
         << endl;
}

void Library::showStats() const {

    if (count == 0) {
        cout << "Library is empty." << endl;
        return;
    }

    cout << "\nTOP 5 MOST PLAYED"
         << endl;

    int limit = (count < 5) ? count : 5;

    bool* used = new bool[count];

    for (int i = 0; i < count; i++) {
        used[i] = false;
    }

    for (int rank = 1; rank <= limit; rank++) {

        int bestIndex = -1;

        for (int i = 0; i < count; i++) {

            if (used[i]) {
                continue;
            }

            if (bestIndex == -1 ||
                items[i]->getPlayCount() >
                items[bestIndex]->getPlayCount()) {

                bestIndex = i;
            }
        }

        used[bestIndex] = true;

        cout << rank
             << ". "
             << items[bestIndex]->getTitle()
             << " "
             << items[bestIndex]->getPlayCount()
             << (items[bestIndex]->getPlayCount() == 1
                     ? " play"
                     : " plays")
             << endl;
    }

    delete[] used;

    int totalSeconds = 0;

    for (int i = 0; i < count; i++) {
        totalSeconds += items[i]->getDuration();
    }

    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    cout << "Library total: "
         << count
         << " items, "
         << setfill('0')
         << setw(2)
         << minutes
         << ":"
         << setw(2)
         << seconds
         << endl;

    cout << setfill(' ');
}

void Library::addToHistory(MediaItem* item) {
    playHistory.push(item);
}

void Library::removeFromHistory(MediaItem* item) {
    playHistory.removeItem(item);
}

void Library::viewHistory() const {
    playHistory.displayHistory();
}