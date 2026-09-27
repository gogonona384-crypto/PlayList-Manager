#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>

#include "HistoryStack.h"
#include "MediaItem.h"

class Library {
private:
    MediaItem** items;
    int capacity;
    int count;

    HistoryStack playHistory;

    void resize();

    void sortByTitleInternal() const;
    bool isTitleSorted() const;

    void printTableHeader() const;
    void printRow(int index) const;

public:
    explicit Library(int initialCapacity = 10);
    ~Library();

    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;

    void addTrack(MediaItem* item);

    void viewALL() const;
    void deleteTrack(int index);

    MediaItem* getTrack(int index) const;

    int getCount() const;

    void binarySearchTitle(const std::string& title);
    void filterLinear(const std::string& query) const;

    void sortLibrary(int option);

    void showStats() const;

    void addToHistory(MediaItem* item);
    void removeFromHistory(MediaItem* item);
    void viewHistory() const;
};

#endif