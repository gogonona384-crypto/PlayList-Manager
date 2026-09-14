#ifndef PLAYQUEUE_H
#define PLAYQUEUE_H

#include <iostream>
#include "Node.h"

using namespace std;

class PlayQueue
{
private :
    Node* front ;
    Node* rear ;

public :
    PlayQueue ()
    {
        front = nullptr ;
        rear = nullptr ;
    }
    void enqueue(MediaItem* item)
    {
        Node* newNode = new  Node (item) ;
        if (front == nullptr)
        {
            front = newNode;
            rear = newNode ;
        }
        else
        {
            rear ->next = newNode ;
            rear = newNode;
        }
    }
    void playNext ()
    {
        if (front == nullptr)
        {
            cout<< "Nothing in the queue" << endl ;
        }
        else
        {
            Node* temp = front ;
            cout<< ">>> NOW PLAYING : ";
            temp->item->play() ;

            front = front->next ;

            if (front == nullptr)
            {
                rear = nullptr;
            }

            delete temp ;
        }
    }
    void displayQueue()
    {
        if (front == nullptr)
        {
            cout << "[X] Nothing in the queue." << endl;
            return;
        }

        Node* current = front;
        int index = 1;
        while (current != nullptr)
        {
            cout << index++ << ". ";
            current->item->play();
            current = current->next;
        }
    }
    ~PlayQueue()
    {
        while (front != nullptr)
        {
            Node* temp = front;
            front = front->next;
            delete temp ;
        }
        rear = nullptr;
    }
};

#endif
