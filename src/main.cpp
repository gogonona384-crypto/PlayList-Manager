#include <iostream>
#include "../include/MediaItem.h"
#include "../include/Song.h"
#include "../include/Podcast.h"

using namespace std;

int main() {
    MediaItem* items[2];

    items[0] = new Song("Bahebak", "Amr Diab", 225, "Pop");
    items[1] = new Podcast("Ep.12 Careers", "Ahmed Samir", 1680, 12);

    cout << "--- Testing Polymorphism ---\n\n";

    for (int i = 0; i < 2; i++) 
    {
        items[i]->play();
        cout << endl;
    }

    for (int i = 0; i < 2; i++) 
    {
        delete items[i];
    }
    cout << "Project Setup Completed Successfully!" << endl;
    return 0;
}