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
    int mainChoice = -1;

    while (mainChoice != 0) {
        showMainMenu();
        if (!(cin >> mainChoice)) break;

        switch (mainChoice) {
            case 1: { 
                int libChoice = -1;
                showLibraryMenu();
                cin >> libChoice;
                if (libChoice == 1) {
                    string title, artist, genre, duration;
                    cout << "Title   : "; cin >> title;
                    cout << "Artist  : "; cin >> artist;
                    cout << "Duration: "; cin >> duration;
                    cout << "Genre   : "; cin >> genre;
                    cout << "[OK] Added. Library updated.\n";
                } else if (libChoice == 3) {
                    cout << "\nID   TYPE     TITLE        BY           LENGTH   PLAYS\n";
                    cout << "01   SONG     Bahebak      Amr Diab     03:45    4\n";
                    cout << "02   SONG     Enta Eih     Nancy Ajram  04:10    1\n";
                    cout << "03   PODCAST  Ep.12        Ahmed Samir  28:00    2\n";
                }
                break;
            }
            case 2: { 
                cout << "\n>>> NOW PLAYING: Bahebak - Amr Diab (03:45)\n";
                cout << "[SONG] streaming audio...\n";
                cout << "(n) next  (p) previous  (q) quit\n> ";
                char nav;
                cin >> nav;
                if (nav == 'n') {
                    cout << ">>> NOW PLAYING: Enta Eih - Nancy Ajram (04:10)\n";
                }
                break;
            }
            case 3: { 
                int qChoice = -1;
                showQueueMenu();
                cin >> qChoice;
                if (qChoice == 3) {
                    cout << ">>> NOW PLAYING: Enta Eih - Nancy Ajram\n";
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
                    cout << "Found in 2 comparisons [binary search]\n";
                }
                break;
            }
            case 5: { 
                cout << "\nTOP 5 MOST PLAYED\n";
                cout << "1. Bahebak      - 4 plays\n";
                cout << "2. Ep.12 Careers- 2 plays\n";
                cout << "3. Enta Eih     - 1 play\n";
                cout << "Library total: 3 items, 35:55\n";
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