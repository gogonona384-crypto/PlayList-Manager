#include <string>
#include <iostream>
#include <limits>
#include "MediaItem.h"
#include "Song.h"
#include "Podcast.h"
#include "Playlist.h"
#include "PlayQueue.h"
#include "Library.h"
#include "Node.h"

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
        cout << "5. Play Next Item in Queue\n";
        cout << "6. Display PlayQueue\n";
        cout << "7. Binary Search by Title\n";
        cout << "8. Linear Filter by Artist/Genre\n";
        cout << "9. Sort Library (Selection Sort)\n";
        cout << "10. Playlist Controls (Next / Prev / Print Backwards)\n";
        cout << "11. Show Library Stats\n";
        cout << "12. View Play History\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid type input!" << endl;
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            string title, artistOrHost;
            int duration;

            cout << "Enter Title: ";
            getline(cin, title);

            cout << "Enter Artist/Host: ";
            getline(cin, artistOrHost);

            cout << "Enter Duration (seconds): ";
            cin >> duration;

            if (cin.fail() || duration < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid duration!" << endl;
                break;
            }

            if (type == 1)
            {
                string genre;
                cout << "Enter Genre: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

                if (cin.fail() || episodeNum < 0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid episode number!" << endl;
                    break;
                }

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
            MediaItem* playedItem = myqueue.playNext();
            if (playedItem != nullptr) {
                mylib.addToHistory(playedItem);
            }
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, searchTitle);
            mylib.binarySearchTitle(searchTitle);
            break;
        }

        case 8: 
        {
            string query;
            cout << "Enter artist or genre to search: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            cout << "1. Play Current Track\n2. Next Track\n3. Previous Track\n4. Print Forwards\n5. Print Backwards (Recursive)\n6. Total Duration (Recursive)\nChoose: ";
            cin >> plChoice;

            MediaItem* playedItem = nullptr;

            if (plChoice == 1) playedItem = myPlayList.playCurrent();
            else if (plChoice == 2) playedItem = myPlayList.nextTrack();
            else if (plChoice == 3) playedItem = myPlayList.prevTrack();
            else if (plChoice == 4) myPlayList.printForwards();
            else if (plChoice == 5) myPlayList.printBackwards();
            else if (plChoice == 6) myPlayList.showTotalDuration();
            else cout << "Invalid choice!" << endl;

            if (playedItem != nullptr) {
                mylib.addToHistory(playedItem);
            }
            break;
        }

        case 11: 
        {
            mylib.showStats();
            break;
        }
        
        case 12: 
        {
            mylib.viewHistory();
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