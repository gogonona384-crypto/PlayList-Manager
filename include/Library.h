#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include "MediaItem.h"

class Library {
private:
    MediaItem** items;
    int capacity;
    int count;

    MediaItem** history;
    int historyCount;
    int historyCapacity;

    void resize();
    void resizeHistory();

public:
    Library(int initialCapacity = 10);
    ~Library();

    void addTrack(MediaItem* item);
    void viewALL() const;
    void deleteTrack(int index);
    MediaItem* getTrack(int index) const;
    int getCount() const;

    void binarySearchTitle(const std::string& title) const;
    void filterLinear(const std::string& query) const;
    void sortLibrary(int option);
    void showStats() const;

    void addToHistory(MediaItem* item);
    void viewHistory() const;
};

#endif