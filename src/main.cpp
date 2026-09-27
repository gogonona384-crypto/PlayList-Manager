#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>

#include "../include/MediaItem.h"
#include "../include/Song.h"
#include "../include/Podcast.h"
#include "../include/Playlist.h"
#include "../include/Library.h"
#include "../include/PlayQueue.h"

using namespace std;


// ======================================================
// INPUT FUNCTIONS
// ======================================================

bool stringToInt(const string& input, int& value)
{
    stringstream ss(input);
    char extra;

    if (!(ss >> value))
        return false;

    if (ss >> extra)
        return false;

    return true;
}


int readInt(const string& prompt, int minValue, int maxValue)
{
    while (true)
    {
        cout << prompt;

        string input;
        getline(cin, input);

        int value;

        if (stringToInt(input, value) &&
            value >= minValue &&
            value <= maxValue)
        {
            return value;
        }

        cout << "[X] Invalid input. Please enter a number from "
             << minValue << " to " << maxValue << ".\n";
    }
}


int readPositiveInt(const string& prompt)
{
    while (true)
    {
        cout << prompt;

        string input;
        getline(cin, input);

        int value;

        if (stringToInt(input, value) && value > 0)
            return value;

        cout << "[X] Please enter a positive number.\n";
    }
}


string readText(const string& prompt)
{
    while (true)
    {
        if (cin.peek() == '\n') cin.ignore();
        cout << prompt;

        string input;
        getline(cin, input);

        if (input.empty())
            continue;

        return input;
    }
}

int readDuration()
{
    while (true)
    {
        string input = readText("Duration: ");

        size_t colon = input.find(':');

        // mm:ss
        if (colon != string::npos)
        {
            string minutePart = input.substr(0, colon);
            string secondPart = input.substr(colon + 1);

            int minutes, seconds;

            if (stringToInt(minutePart, minutes) &&
                stringToInt(secondPart, seconds) &&
                minutes >= 0 && seconds >= 0 && seconds <= 59)
            {
                return minutes * 60 + seconds;
            }
        }
        // seconds
        else
        {
            int seconds;
            if (stringToInt(input, seconds) && seconds >= 0)
            {
                return seconds;
            }
        }

        cout << "[X] Invalid duration. Example: 03:45\n";
    }
}
// ======================================================
// MENUS
// ======================================================

void showMainMenu()
{
    cout << "\n";
    cout << "=========================================\n";
    cout << "            PLAYLIST MANAGER\n";
    cout << "=========================================\n";
    cout << "1. Library\n";
    cout << "2. Playlist\n";
    cout << "3. Up Next queue\n";
    cout << "4. Search and sort\n";
    cout << "5. Stats\n";
    cout << "0. Exit\n";
    cout << "-----------------------------------------\n";
}


void showLibraryMenu()
{
    cout << "\n";
    cout << "------------- LIBRARY -------------------\n";
    cout << "1. Add song\n";
    cout << "2. Add podcast\n";
    cout << "3. View all\n";
    cout << "4. Delete item\n";
    cout << "0. Back\n";
    cout << "-----------------------------------------\n";
}


void showPlaylistMenu()
{
    cout << "\n";
    cout << "------------- PLAYLIST ------------------\n";
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
}


void showQueueMenu()
{
    cout << "\n";
    cout << "------------- UP NEXT -------------------\n";
    cout << "1. Add to queue\n";
    cout << "2. View queue\n";
    cout << "3. Play next from queue\n";
    cout << "0. Back\n";
    cout << "-----------------------------------------\n";
}


void showSearchSortMenu()
{
    cout << "\n";
    cout << "--------- SEARCH / SORT -----------------\n";
    cout << "1. Search by exact title\n";
    cout << "2. Filter by artist or genre\n";
    cout << "3. Sort library\n";
    cout << "0. Back\n";
    cout << "-----------------------------------------\n";
}


// ======================================================
// LIBRARY MENU
// ======================================================

void handleLibrary(
    Library& library,
    Playlist& playlist,
    PlayQueue& queue
)
{
    int choice = -1;

    while (choice != 0)
    {
        showLibraryMenu();

        choice = readInt("Choose: ", 0, 4);

        switch (choice)
        {
            // ------------------------------------------
            // ADD SONG
            // ------------------------------------------
            case 1:
            {
                cout << "\n------------- ADD SONG ------------------\n";

                string title = readText("Title   : ");
                string artist = readText("Artist  : ");

                int duration = readDuration();

                string genre = readText("Genre   : ");

                MediaItem* song =
                    new Song(
                        title,
                        artist,
                        duration,
                        genre
                    );

                library.addTrack(song);

                break;
            }


            // ------------------------------------------
            // ADD PODCAST
            // ------------------------------------------
            case 2:
            {
                cout << "\n----------- ADD PODCAST -----------------\n";

                string title = readText("Title   : ");
                string host = readText("Host    : ");

                int duration = readDuration();

                int episode = readPositiveInt("Episode : ");

                MediaItem* podcast =
                    new Podcast(
                        title,
                        host,
                        duration,
                        episode
                    );

                library.addTrack(podcast);

                break;
            }


            // ------------------------------------------
            // VIEW ALL
            // ------------------------------------------
            case 3:
            {
                library.viewALL();
                break;
            }


            // ------------------------------------------
            // DELETE ITEM
            // ------------------------------------------
            case 4:
            {
                if (library.getCount() == 0)
                {
                    cout << "Library is empty.\n";
                    break;
                }

                int trackID =
                    readInt(
                        "Track ID: ",
                        1,
                        library.getCount()
                    );

                MediaItem* item =
                    library.getTrack(trackID - 1);

                if (item == nullptr)
                {
                    cout << "[X] Invalid track ID.\n";
                    break;
                }

                playlist.removeItem(item);
                queue.removeItem(item);

                library.deleteTrack(trackID - 1);

                break;
            }


            case 0:
                break;
        }
    }
}


// ======================================================
// PLAYLIST MENU
// ======================================================

void handlePlaylist(
    Library& library,
    Playlist& playlist
)
{
    int choice = -1;

    while (choice != 0)
    {
        showPlaylistMenu();

        choice = readInt("Choose: ", 0, 8);

        switch (choice)
        {
            // ------------------------------------------
            // ADD TRACK
            // ------------------------------------------
            case 1:
            {
                if (library.getCount() == 0)
                {
                    cout << "[X] Library is empty. "
                         << "Add tracks first.\n";
                    break;
                }

                int trackID =
                    readInt(
                        "Track ID: ",
                        1,
                        library.getCount()
                    );

                MediaItem* item =
                    library.getTrack(trackID - 1);

                if (item == nullptr)
                {
                    cout << "[X] Invalid track ID.\n";
                }
                else
                {
                    playlist.addTrack(item);
                }

                break;
            }


            // ------------------------------------------
            // REMOVE TRACK
            // ------------------------------------------
            case 2:
            {
                if (library.getCount() == 0)
                {
                    cout << "[X] Library is empty.\n";
                    break;
                }

                int index =
                    readPositiveInt(
                        "Track index to remove: "
                    );

                playlist.removeTrack(index);

                break;
            }


            // ------------------------------------------
            // PLAY
            // ------------------------------------------
            case 3:
            {
                MediaItem* current =
                    playlist.playCurrent();

                if (current == nullptr)
                    break;

                cout << "(n) next (p) previous (q) quit\n";

                while (true)
                {
                    cout << "> ";

                    string input;
                    getline(cin, input);

                    if (input.size() != 1)
                    {
                        cout << "[X] Enter n, p or q.\n";
                        continue;
                    }

                    char command =
                        static_cast<char>(
                            tolower(
                                static_cast<unsigned char>(
                                    input[0]
                                )
                            )
                        );

                    if (command == 'q')
                    {
                        break;
                    }

                    if (command == 'n')
                    {
                        playlist.nextTrack();
                    }
                    else if (command == 'p')
                    {
                        playlist.prevTrack();
                    }
                    else
                    {
                        cout << "[X] Invalid command.\n";
                    }
                }

                break;
            }


            // ------------------------------------------
            // NEXT
            // ------------------------------------------
            case 4:
            {
                playlist.nextTrack();
                break;
            }


            // ------------------------------------------
            // PREVIOUS
            // ------------------------------------------
            case 5:
            {
                playlist.prevTrack();
                break;
            }


            // ------------------------------------------
            // FORWARDS
            // ------------------------------------------
            case 6:
            {
                playlist.printForwards();
                break;
            }


            // ------------------------------------------
            // BACKWARDS
            // ------------------------------------------
            case 7:
            {
                playlist.printBackwards();
                break;
            }


            // ------------------------------------------
            // TOTAL DURATION
            // ------------------------------------------
            case 8:
            {
                playlist.showTotalDuration();
                break;
            }


            case 0:
                break;
        }
    }
}


// ======================================================
// QUEUE MENU
// ======================================================

void handleQueue(
    Library& library,
    PlayQueue& queue
)
{
    int choice = -1;

    while (choice != 0)
    {
        showQueueMenu();

        choice = readInt("Choose: ", 0, 3);

        switch (choice)
        {
            // ------------------------------------------
            // ADD TO QUEUE
            // ------------------------------------------
            case 1:
            {
                if (library.getCount() == 0)
                {
                    cout << "[X] Library is empty. "
                         << "Add tracks first.\n";
                    break;
                }

                int trackID =
                    readInt(
                        "Track ID: ",
                        1,
                        library.getCount()
                    );

                MediaItem* item =
                    library.getTrack(trackID - 1);

                if (item == nullptr)
                {
                    cout << "[X] Invalid track ID.\n";
                }
                else
                {
                    queue.enqueue(item);
                }

                break;
            }


            // ------------------------------------------
            // VIEW QUEUE
            // ------------------------------------------
            case 2:
            {
                queue.displayQueue();
                break;
            }


            // ------------------------------------------
            // PLAY NEXT
            // ------------------------------------------
            case 3:
            {
                queue.playNext();
                break;
            }


            case 0:
                break;
        }
    }
}


// ======================================================
// SEARCH / SORT MENU
// ======================================================

void handleSearchSort(Library& library)
{
    int choice = -1;

    while (choice != 0)
    {
        showSearchSortMenu();

        choice = readInt("Choose: ", 0, 3);

        switch (choice)
        {
            // ------------------------------------------
            // BINARY SEARCH
            // ------------------------------------------
            case 1:
            {
                if (library.getCount() == 0)
                {
                    cout << "Library is empty.\n";
                    break;
                }

                string title =
                    readText("Title: ");

                library.binarySearchTitle(title);

                break;
            }


            // ------------------------------------------
            // LINEAR SEARCH
            // ------------------------------------------
            case 2:
            {
                if (library.getCount() == 0)
                {
                    cout << "Library is empty.\n";
                    break;
                }

                string query =
                    readText("Genre/Artist: ");

                library.filterLinear(query);

                break;
            }


            // ------------------------------------------
            // SORT
            // ------------------------------------------
            case 3:
            {
                if (library.getCount() < 2)
                {
                    cout << "[X] Need at least 2 items to sort.\n";
                    break;
                }

                int sortOption =
                    readInt(
                        "Sort by (1) title "
                        "(2) duration "
                        "(3) play count: ",
                        1,
                        3
                    );

                library.sortLibrary(sortOption);

                break;
            }


            case 0:
                break;
        }
    }
}


// ======================================================
// MAIN
// ======================================================

int main()
{
    Library library;
    Playlist playlist;
    PlayQueue queue;

    int choice = -1;

    while (choice != 0)
    {
        showMainMenu();

        choice = readInt(
            "Choose: ",
            0,
            5
        );

        switch (choice)
        {
            case 1:
            {
                handleLibrary(
                    library,
                    playlist,
                    queue
                );

                break;
            }


            case 2:
            {
                handlePlaylist(
                    library,
                    playlist
                );

                break;
            }


            case 3:
            {
                handleQueue(
                    library,
                    queue
                );

                break;
            }


            case 4:
            {
                handleSearchSort(library);

                break;
            }


            case 5:
            {
                library.showStats();

                break;
            }


            case 0:
            {
                cout << "\nExiting Playlist Manager...\n";
                break;
            }
        }
    }

    return 0;
}