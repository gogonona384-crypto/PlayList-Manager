#include <iostream>
#include <string>
#include "../include/MediaItem.h"
#include "../include/Song.h"
#include "../include/Podcast.h"
#include "../include/Playlist.h"
#include "../include/Library.h"
#include "../include/PlayQueue.h"
#include "../include/HistoryStack.h"

using namespace std;


void showMainMenu() {
    cout << "\nPLAYLIST MANAGER\n";
    cout << "1. Library\n";
    cout << "2. Playlist\n";
    cout << "3. Up Next queue\n";
    cout << "4. Search and sort\n";
    cout << "5. Stats\n";
    cout << "0. Exit\n";
    cout << "Choose: ";
}

void showLibraryMenu() {
    cout << "\nLIBRARY\n";
    cout << "1. Add song\n";
    cout << "2. Add podcast\n";
    cout << "3. View all\n";
    cout << "4. Delete item\n";
    cout << "0. Back\n";
    cout << "Choose: ";
}

void showQueueMenu() {
    cout << "\nUP NEXT\n";
    cout << "1. Add to queue\n";
    cout << "2. View queue\n";
    cout << "3. Play next from queue\n";
    cout << "0. Back\n";
    cout << "Choose: ";
}

void showSearchSortMenu() {
    cout << "\n1. Search by exact title\n";
    cout << "2. Filter by artist or genre\n";
    cout << "3. Sort library\n";
    cout << "Choose: ";
}

int main() {
    Library library;
    PlayQueue playQueue;
    Playlist playlist;
    int mainChoice = -1;

    while (mainChoice != 0) {
        showMainMenu();
        if (!(cin >> mainChoice)) break;

        switch (mainChoice) 
        {
            case 1: { 
                int libChoice = -1;
                showLibraryMenu();
                cin >> libChoice;
                if (libChoice == 1) {
                    string title, artist, genre;
                    int duration;
                    cout << "Title   : "; cin >> title;
                    cout << "Artist  : "; cin >> artist;
                    cout << "Duration: "; cin >> duration;
                    cout << "Genre   : "; cin >> genre;
                   library.addTrack(new Song(title, artist, duration, genre));
                    cout << "[OK] Added. Library updated.\n";
                } 
                else if (libChoice == 2)
                 {
                string title, host;
                int episode , duration;
        cout << "Title   : "; cin >> title;
        cout << "Host    : "; cin >> host;
        cout << "Duration: "; cin >> duration;
        cout << "Episode : "; cin >> episode;
        library.addTrack(new Podcast(title, host, duration, episode));
                }
                else if (libChoice == 3) 
                {
                    library.viewALL();
                }
                else if (libChoice == 4) 
                {
                    int index;
                    cout << "Enter index to delete: "; cin >> index;
                    library.deleteTrack(index);
                }
                break;
            }
            case 2:
         { 
             int pChoice = -1;

          while (pChoice != 0) {
           cout << "\n------------- PLAYLIST -----------------\n";
            cout << "1. Add track\n";
            cout << "2. Remove track\n";
            cout << "3. Play current track\n";
            cout << "4. Next track\n";
            cout << "5. Previous track\n";
            cout << "6. Print forwards\n";
            cout << "7. Print backwards\n";
            cout << "8. Total duration\n";
            cout << "0. Back\n";
            cout << "-----------------------------------------\n";
            cout << "Choose: ";
            cin >> pChoice;

        if (pChoice == 1) {
            int trackNumber;
            cout << "Track ID: ";
            cin >> trackNumber;

            MediaItem* item = library.getTrack(trackNumber - 1);

            if (item == nullptr) {
                cout << "[X] Invalid track ID!\n";
            } else {
                playlist.addTrack(item);
            }
        }

        else if (pChoice == 2) {
            int index;
            cout << "Track index to remove: ";
            cin >> index;
            playlist.removeTrack(index);
        }

        else if (pChoice == 3) {
    playlist.playCurrent();

    char command;
    cout << "(n) next (p) previous (q) quit\n";
    cin >> command;

    while (command != 'q') {

        if (command == 'n') {
            playlist.nextTrack();
        }
        else if (command == 'p') {
            playlist.prevTrack();
        }
        else {
            cout << "[X] Invalid command.\n";
        }

        if (command != 'q') {
            cin >> command;
        }
    }
}

        else if (pChoice == 4) {
            playlist.nextTrack();
        }

        else if (pChoice == 5) {
            playlist.prevTrack();
        }

        else if (pChoice == 6) {
            playlist.printForwards();
        }

        else if (pChoice == 7) {
            playlist.printBackwards();
        }

        else if (pChoice == 8) {
            playlist.showTotalDuration();
        }

        else if (pChoice != 0) {
            cout << "[X] Invalid choice!\n";
        }
    }

    break;
}
            case 3: {
    int qChoice = -1;

    while (qChoice != 0) {
        showQueueMenu();
        cin >> qChoice;

        if (qChoice == 1) {
            int trackNumber;
            cout << "Track ID: ";
            cin >> trackNumber;

            MediaItem* item = library.getTrack(trackNumber - 1);

            if (item == nullptr) {
                cout << "[X] Invalid track ID!\n";
            } else {
                playQueue.enqueue(item);
            }
        }

        else if (qChoice == 2) {
            playQueue.displayQueue();
        }

        else if (qChoice == 3) {
            playQueue.playNext();
        }

        else if (qChoice != 0) {
            cout << "[X] Invalid choice!\n";
        }
    }

    break;
}
            case 4: { 
                int ssChoice = -1;
                showSearchSortMenu();
                cin >> ssChoice;
                if (ssChoice == 1) {
                    string query;
                    cout << "Title: "; cin >> query;
                    library.binarySearchTitle(query);
                } else if (ssChoice == 2) {
                    string query;
                    cout << "Genre/Artist: "; cin >> query;
                    library.filterLinear(query);
                } else if (ssChoice == 3) {
                    int sortOpt;
                    cout << "Sort by (1) title (2) duration (3) play count: ";
                    cin >> sortOpt;
                    library.sortLibrary(sortOpt);
                }
                break;
            }
            case 5: { 
                library.showStats();
                break;
            }
            case 0:
                cout << "\nExiting Playlist Manager...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}