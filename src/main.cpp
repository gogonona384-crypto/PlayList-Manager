#include <iostream>
#include <string>
#include "../include/MediaItem.h"
#include "../include/Song.h"
#include "../include/Podcast.h"
#include "../include/Playlist.h"
#include "../include/PlayQueue.h"
#include "../include/Library.h"
#include "../include/Node.h"

using namespace std;

int main()
{
    Library mylib;
    PlayQueue myqueue;
    Playlist myPlayList;
    int choice = -1;

    while (choice != 0)
    {
        cout << "\n=== Playlist Manager ===" << endl;
        cout << "1. Add Item to Library" << endl;
        cout << "2. View Library" << endl;
        cout << "3. Delete Item from Library" << endl;
        cout << "4. Enqueue Item to PlayQueue" << endl;
        cout << "5. Play Next from Queue" << endl;
        cout << "6. View Queue" << endl;
        cout << "7. Search Item by Title" << endl;
        cout << "8. Search Item by Artist/Host" << endl;
        cout << "9. Sort Library by Title" << endl;
        cout << "10. Show Library Stats" << endl;
        cout << "0. Exit" << endl;
        cout << "========================" << endl;
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            int type;
            cout << "1. Song\n2. Podcast\nChoose type: ";
            cin >> type;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid type input!" << endl;
                break;
            }

            cin.ignore(10000, '\n'); 
            string title, artistOrHost;
            int duration;

            cout << "Enter Title: ";
            getline(cin, title);

            cout << "Enter Artist/Host: ";
            getline(cin, artistOrHost);

            cout << "Enter Duration (seconds): ";
            cin >> duration;

            if (type == 1)
            {
                string genre;
                cout << "Enter Genre: ";
                cin.ignore(10000, '\n');
                getline(cin, genre);

                mylib.addItem(new Song(title, artistOrHost, duration, genre));
                cout << "Song added successfully!" << endl;
            }
            else if (type == 2)
            {
                int episodeNum;
                cout << "Enter Episode Number: ";
                cin >> episodeNum;

                mylib.addItem(new Podcast(title, artistOrHost, duration, episodeNum));
                cout << "Podcast added successfully!" << endl;
            }
            else
            {
                cout << "Invalid type!" << endl;
            }
            break;
        }
        case 2:
        {
            mylib.viewALL();
            break;
        }

        case 3:
        {
            int index;
            cout << "Enter Item ID to delete: ";
            cin >> index;
            mylib.deleteItem(index - 1);
            break;
        }
        case 4:
        {
            int index;
            cout << "Enter Item ID to enqueue: ";
            cin >> index;

            MediaItem* item = mylib.getItem(index - 1);
            if (item != nullptr)
            {
                myqueue.enqueue(item);
                cout << "Item enqueued successfully!" << endl;
            }
            else
            {
                cout << "Invalid Item ID!" << endl;
            }
            break;
        }
        case 5:
            myqueue.playNext();
            break;

        case 6:
            myqueue.displayQueue();
            break;
            
        case 7 :
        {
        string searchTitle;

         cout<<"Enter exact title to search :" ;
         cin.ignore();
        getline(cin,searchTitle);

          mylib.searchItem(searchTitle);
        break;
         }

         case 8 :
        {
        string artistName;
        cout<<"Enter exact artist name to search :" ;
        cin.ignore();
        getline(cin,artistName);

         mylib.searchItem(artistName);
        break;
        }
        case 9 :
        {
        mylib.sortLibrary();
            break;
        }
        case 10 :
        {
        mylib.showStats();
        break;
        }
        case 0:        
            cout << "Exiting Program ..." << endl;
            break;

        default:
            cout << "Invalid choice! Try again." << endl;
            break;
        }
    }
    return 0;
}
