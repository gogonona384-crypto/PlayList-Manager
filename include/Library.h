#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include <iomanip>
#include "MediaItem.h"
#include "Song.h"
#include "Podcast.h"

using namespace std;

class Library
{
private:
    MediaItem* items[100];
    int itemCount = 0;

public:
    Library()
    {
        itemCount = 0;
        for (int i = 0; i < 100; i++)
        {
            items[i] = nullptr;
        }
    }

    MediaItem* getItem(int index)
    {
        if (index >= 0 && index < itemCount)
        {
            return items[index];
        }
        cout << "Invalid index!" << endl;
        return nullptr;
    }

    int getItemCount() const
    {
        return itemCount;
    }

    void addItem(MediaItem* item)
    {
        if (itemCount >= 100)
        {
            cout << "Library is full!\n";
        }
        else
        {
            items[itemCount] = item;
            itemCount++;
            cout << "[OK] Added. Library has " << itemCount << " items." << endl;
        }
    }

    void viewALL()
    {
        if (itemCount == 0)
        {
            cout << "Library is empty!\n";
            return;
        }
        cout << "ID\tTYPE\t\tTITLE\t\tBY\t\tLENGTH\tPLAYS" << endl;
        for (int i = 0; i < itemCount; i++)
        {
            cout << setfill('0') << setw(2) << (i + 1) << "\t";
            
            if (dynamic_cast<Song*>(items[i]))
                cout << "SONG\t\t";
            else if (dynamic_cast<Podcast*>(items[i]))
                cout << "PODCAST\t\t";

            items[i]->getInfo();
            cout << endl;
        }
    }

    void deleteItem(int index)
    {
        if (index >= 0 && index < itemCount)
        {
            delete items[index];
            for (int i = index; i < itemCount - 1; i++)
            {
                items[i] = items[i + 1];
            }
            items[itemCount - 1] = nullptr;
            itemCount--;
            cout << "[OK] Item deleted successfully." << endl;
        }
        else
        {
            cout << "Invalid index!" << endl;
        }
    }

    MediaItem* binarySearchTitle(string query)
    {
        int low = 0;
        int high = itemCount - 1;
        int comparisons = 0;

        while (low <= high)
        {
            comparisons++;
            int mid = low + (high - low) / 2;

            if (items[mid]->getTitle() == query)
            {
                cout << "Found in " << comparisons << " comparisons [binary search]" << endl;
                cout << setfill('0') << setw(2) << (mid + 1) << " ";
                items[mid]->getInfo();
                cout << endl;
                return items[mid];
            }

            if (items[mid]->getTitle() < query)
                low = mid + 1;
            else
                high = mid - 1;
        }

        cout << "Item not found! Comparisons: " << comparisons << endl;
        return nullptr;
    }

    void filterLinear(string query)
    {
        int comparisons = 0;
        int matches = 0;

        for (int i = 0; i < itemCount; i++)
        {
            comparisons++;
            
            Song* song = dynamic_cast<Song*>(items[i]);
            if (song)
            {
                if (song->getGenre() == query || song->getArtist() == query)
                {
                    cout << setfill('0') << setw(2) << (i + 1) << " ";
                    song->getInfo();
                    cout << endl;
                    matches++;
                    continue;
                }
            }

            Podcast* podcast = dynamic_cast<Podcast*>(items[i]);
            if (podcast)
            {
                if (podcast->getHost() == query)
                {
                    cout << setfill('0') << setw(2) << (i + 1) << " ";
                    podcast->getInfo();
                    cout << endl;
                    matches++;
                }
            }
        }
        cout << matches << " matches [linear search]" << endl;
    }

    void sortLibrary(int sortBy = 1)
    {
        int comparisons = 0;
        for (int i = 0; i < itemCount - 1; i++)
        {
            int targetIdx = i;
            for (int j = i + 1; j < itemCount; j++)
            {
                comparisons++;
                bool condition = false;

                if (sortBy == 1) 
                    condition = (items[j]->getTitle() < items[targetIdx]->getTitle());
                else if (sortBy == 2) 
                    condition = (items[j]->getDuration() < items[targetIdx]->getDuration());
                else if (sortBy == 3) 
                    condition = (items[j]->getPlayCount() > items[targetIdx]->getPlayCount());

                if (condition)
                {
                    targetIdx = j;
                }
            }
            if (targetIdx != i)
            {
                swap(items[i], items[targetIdx]);
            }
        }
        cout << "Sorted in " << comparisons << " comparisons [selection sort]" << endl;
    }

    void showStats()
    {
        cout << "TOP 5 MOST PLAYED" << endl;

        MediaItem* temp[100];
        for (int i = 0; i < itemCount; i++) temp[i] = items[i];

        for (int i = 0; i < itemCount - 1; i++)
        {
            for (int j = i + 1; j < itemCount; j++)
            {
                if (temp[j]->getPlayCount() > temp[i]->getPlayCount())
                {
                    swap(temp[i], temp[j]);
                }
            }
        }

        int topCount = (itemCount < 5) ? itemCount : 5;
        for (int i = 0; i < topCount; i++)
        {
            cout << (i + 1) << ". " << temp[i]->getTitle() << " " 
                 << temp[i]->getPlayCount() << " plays" << endl;
        }

        int totalDuration = 0;
        for (int i = 0; i < itemCount; i++)
        {
            totalDuration += items[i]->getDuration();
        }

        int mins = totalDuration / 60;
        int secs = totalDuration % 60;

        cout << "\nLibrary total: " << itemCount << " items, " 
             << setfill('0') << setw(2) << mins << ":" 
             << setfill('0') << setw(2) << secs << endl;
    }

    ~Library()
    {
        for (int i = 0; i < itemCount; i++)
        {
            delete items[i];
            items[i] = nullptr;
        }
    }
};

#endif