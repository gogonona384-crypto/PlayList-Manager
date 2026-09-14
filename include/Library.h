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
