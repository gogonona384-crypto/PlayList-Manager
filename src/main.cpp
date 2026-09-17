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
        cout << "\n=== Playlist Manager ===\n";
        cout << "1. Add Item to Library\n";
        cout << "2. View Library\n";
        cout << "3. Delete Item from Library\n";
        cout << "4. Enqueue Item to PlayQueue\n";
        cout << "5. Play Next from Queue\n";
        cout << "6. View PlayQueue\n";
        cout << "7. Search by Title (Binary Search)\n";
        cout << "8. Filter by Artist/Genre (Linear Search)\n";
        cout << "9. Sort Library (Selection Sort)\n";
        cout << "10. Playlist Controls (Next / Prev / Print Backwards)\n";
        cout << "11. Show Library Stats\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
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

                Song* newSong = new Song(title, artistOrHost, duration, genre);
                mylib.addItem(newSong);
                myPlayList.addTrack(newSong);
                cout << "[OK] Song added successfully!" << endl;
            }
            else if (type == 2)
            {
                int episodeNum;
                cout << "Enter Episode Number: ";
                cin >> episodeNum;

                Podcast* newPodcast = new Podcast(title, artistOrHost, duration, episodeNum);
                mylib.addItem(newPodcast);  
                myPlayList.addTrack(newPodcast);
                cout << "[OK] Podcast added successfully!" << endl;
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
            }
            else
            {
                cout << "Invalid Item ID!" << endl;
            }
            break;
        }

        case 5: 
        {
            myqueue.playNext();
            break;
        }

        case 6: 
        {
            myqueue.displayQueue();
            break;
        }
            
        case 7: 
        {
            string searchTitle;
            cout << "Enter exact title to search (Array must be sorted first): ";
            cin.ignore(10000, '\n');
            getline(cin, searchTitle);
            mylib.binarySearchTitle(searchTitle);
            break;
        }

        case 8: 
        {
            string query;
            cout << "Enter artist or genre to search: ";
            cin.ignore(10000, '\n');
            getline(cin, query);
            mylib.filterLinear(query);
            break;
        }

        case 9: 
        {
            int sortOption;
            cout << "Sort by:\n1. Title (A-Z)\n2. Duration\n3. Play Count\nChoose option: ";
            cin >> sortOption;

            if (sortOption >= 1 && sortOption <= 3) 
            {
                mylib.sortLibrary(sortOption);
            }
            else 
            {
                cout << "Invalid sort option!" << endl;
            }
            break;
        }

        case 10: 
        {
            int plChoice;
            cout << "\n--- Playlist Controls ---\n";
            cout << "1. Next Track\n2. Previous Track\n3. Print Forwards\n4. Print Backwards (Recursive)\n5. Total Duration (Recursive)\nChoose: ";
            cin >> plChoice;

            if (plChoice == 1) myPlayList.nextTrack();
            else if (plChoice == 2) myPlayList.prevTrack();
            else if (plChoice == 3) myPlayList.printForwards();
            else if (plChoice == 4) myPlayList.printBackwards();
            else if (plChoice == 5) myPlayList.showTotalDuration();
            else cout << "Invalid choice!" << endl;
            break;
        }

        case 11: 
        {
            mylib.showStats();
            break;
        }

        case 0:      
        {
            cout << "Exiting Program ..." << endl;
            break;
        }

        default:
        {
            cout << "Invalid choice! Try again." << endl;
            break;
        }
        }
    }
    return 0;
}