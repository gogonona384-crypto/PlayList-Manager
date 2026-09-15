#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include "MediaItem.h"
#include "Song.h"
#include "Podcast.h"

using namespace std;

class Library
{
private :

    MediaItem* items[100];
    int itemCount = 0;

public :
    Library()
    {
        itemCount = 0;
        for (int i = 0; i<100 ; i++)
        {
            items [i] = nullptr;
        }
    }
    MediaItem* getItem(int index)
    {
        return items[index];
    }
    void addItem (MediaItem* item)
    {
        if (itemCount >=100)
        {
            cout<< "Library is full !" <<"\n" ;
        }
        else
        {
            items[itemCount] = item;
            itemCount++;
            cout<<" [OK] Added. Library has  " << itemCount << " items." << endl;
        }
    }
    void viewALL ()
    {
        if (itemCount == 0)
        {
            cout<< "Library is empty !" <<"\n" ;
            return;
        }
        cout<< "ID\tTYPE \tTITLE\tBY\tLENGTH\tPLAYS"<<endl;
        for (int i = 0 ; i<itemCount ; i++)
        {
            cout<< (i + 1)<<"\t" ;
            items[i]->getInfo();
            cout<<endl;
        }
    }
    void deleteItem(int index)
    {
        if ( index >=0 && index < itemCount )
        {
            delete items[index];
            for (int i = index ; i<itemCount -1 ; i++)
            {
                items[i] = items[i + 1] ;
            }
            items[itemCount - 1 ] = nullptr;
            itemCount--;
            cout<< "[OK] Item deleted successfully ." <<endl;
        }
        else
        {
            cout<< "Invalid index!" <<endl;
        }
    }
    void searchItem(string query)
    {
        bool found = false;
        int comparisons = 0;
        for (int i = 0; i < itemCount; i++)
        {
            comparisons++;
            if (items[i]->getTitle() == query )
            {
                cout << "Found item: ";
                items[i]->getInfo();
                cout << endl;
                found = true;
            }
        }
        if (!found) cout << "Item not found!" << endl;
        cout << "Comparisons count: " << comparisons << endl;
    }

    void sortLibrary()
    {
        int comparisons = 0;
        for (int i = 0; i < itemCount - 1; i++)
        {
            int minIdx = i;
            for (int j = i + 1; j < itemCount; j++)
            {
                comparisons++;
                if (items[j]->getTitle() < items[minIdx]->getTitle())
                {
                    minIdx = j;
                }
            }
            if (minIdx != i)
            {
                swap(items[i], items[minIdx]);
            }
        }
        cout << "Library sorted successfully!" << endl;
        cout << "Comparisons count: " << comparisons << endl;
    }

    void showStats()
    {
        cout << "Total Items: " << itemCount << endl;
        int totalDuration = 0;
        for (int i = 0; i < itemCount; i++)
        {
            totalDuration += items[i]->getDuration();
        }
        cout << "Total Duration: " << totalDuration << " seconds" << endl;
    }
        ~Library()
        {
            for (int i = 0 ; i < itemCount ; i++ )
            {
                delete items[i];
                items[i] = nullptr;
            }
        }
};
#endif
