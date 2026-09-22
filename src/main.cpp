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
        cout << "\n===================================\n";
        cout << "      PLAYLIST MANAGER MAIN MENU    \n";
        cout << "===================================\n";
        cout << "1. Library Management\n";
        cout << "2. Playlist Operations\n";
        cout << "3. Up Next Queue\n";
        cout << "4. Search and Sort\n";
        cout << "5. Library Stats\n";
        cout << "6. View Play History (Bonus)\n";
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
            int libChoice = -1;
            cout << "\n--- LIBRARY ---\n";
            cout << "1. Add Song\n2. Add Podcast\n3. View All\n4. Delete Item\n0. Back\nChoose: ";
            cin >> libChoice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid option!" << endl;
                break;
            }

            if (libChoice == 1) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string title, artist, genre;
                int duration;

                cout << "Title  : "; getline(cin, title);
                cout << "Artist : "; getline(cin, artist);
                cout << "Duration (seconds): "; cin >> duration;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Genre  : "; getline(cin, genre);

                if (duration >= 0) {
                    Song* newSong = new Song(title, artist, duration, genre);
                    mylib.addItem(newSong);
                } else {
                    cout << "Invalid duration!" << endl;
                }
            }
            else if (libChoice == 2) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string title, host;
                int duration, epNum;

                cout << "Title  : "; getline(cin, title);
                cout << "Host   : "; getline(cin, host);
                cout << "Duration (seconds): "; cin >> duration;
                cout << "Episode Number   : "; cin >> epNum;

                if (duration >= 0 && epNum >= 0) {
                    Podcast* newPod = new Podcast(title, host, duration, epNum);
                    mylib.addItem(newPod);
                } else {
                    cout << "Invalid inputs!" << endl;
                }
            }
            else if (libChoice == 3) {
                mylib.viewALL();
            }
            else if (libChoice == 4) {
                int index;
                cout << "Enter Item ID to delete: ";
                cin >> index;
                mylib.deleteItem(index - 1);
            }
            break;
        }

        case 2: 
        {
            int plChoice = -1;
            cout << "\n--- PLAYLIST MENU ---\n";
            cout << "1. Add Track from Library to Playlist\n";
            cout << "2. Remove Track from Playlist\n";
            cout << "3. Play Interactive Controls (Next/Prev)\n";
            cout << "4. Print Forwards\n";
            cout << "5. Print Backwards (Recursive)\n";
            cout << "6. Total Duration (Recursive)\n";
            cout << "0. Back\nChoose: ";
            cin >> plChoice;

            if (plChoice == 1) {
                int id;
                cout << "Enter Track ID from Library: ";
                cin >> id;
                MediaItem* item = mylib.getItem(id - 1);
                if (item) {
                    myPlayList.addTrack(item);
                } else {
                    cout << "Invalid ID!" << endl;
                }
            }
            else if (plChoice == 2) {
                int pos;
                cout << "Enter Track Position to remove: ";
                cin >> pos;
                myPlayList.removeTrack(pos);
            }
            else if (plChoice == 3) {
                char nav = ' ';
                MediaItem* played = myPlayList.playCurrent();
                if (played) mylib.addToHistory(played);

                while (nav != 'q' && nav != 'Q' && played != nullptr) {
                    cout << "(n) next (p) previous (q) quit\n> ";
                    cin >> nav;
                    if (nav == 'n' || nav == 'N') {
                        played = myPlayList.nextTrack();
                        if (played) mylib.addToHistory(played);
                    } else if (nav == 'p' || nav == 'P') {
                        played = myPlayList.prevTrack();
                        if (played) mylib.addToHistory(played);
                    }
                }
            }
            else if (plChoice == 4) myPlayList.printForwards();
            else if (plChoice == 5) myPlayList.printBackwards();
            else if (plChoice == 6) myPlayList.showTotalDuration();
            break;
        }

        case 3: 
        {
            int qChoice = -1;
            cout << "\n--- UP NEXT QUEUE ---\n";
            cout << "1. Add to queue\n2. View queue\n3. Play next from queue\n0. Back\nChoose: ";
            cin >> qChoice;

            if (qChoice == 1) {
                int id;
                cout << "Track ID from Library: ";
                cin >> id;
                MediaItem* item = mylib.getItem(id - 1);
                if (item) myqueue.enqueue(item);
                else cout << "Invalid Track ID!" << endl;
            }
            else if (qChoice == 2) {
                myqueue.displayQueue();
            }
            else if (qChoice == 3) {
                MediaItem* played = myqueue.playNext();
                if (played) mylib.addToHistory(played);
            }
            break;
        }

        case 4: 
        {
            int ssChoice = -1;
            cout << "\n--- SEARCH AND SORT ---\n";
            cout << "1. Search by exact title (Binary Search)\n";
            cout << "2. Filter by artist or genre (Linear Search)\n";
            cout << "3. Sort library (Selection Sort)\n";
            cout << "0. Back\nChoose: ";
            cin >> ssChoice;

            if (ssChoice == 1) {
                string searchTitle;
                cout << "Title: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, searchTitle);
                mylib.binarySearchTitle(searchTitle);
            }
            else if (ssChoice == 2) {
                string query;
                cout << "Genre or Artist: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, query);
                mylib.filterLinear(query);
            }
            else if (ssChoice == 3) {
                int sortOpt;
                cout << "Sort by (1) title (2) duration (3) play count: ";
                cin >> sortOpt;
                if (sortOpt >= 1 && sortOpt <= 3) {
                    mylib.sortLibrary(sortOpt);
                } else {
                    cout << "Invalid sort option!" << endl;
                }
            }
            break;
        }

        case 5: 
        {
            mylib.showStats();
            break;
        }

        case 6: 
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
            cout << "Invalid choice! Try again." << endl;
            break;
        }
    }
    return 0;
}