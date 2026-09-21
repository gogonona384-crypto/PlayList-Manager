#ifndef PLAYQUEUE_H
#define PLAYQUEUE_H

#include <iostream>
#include "Node.h"

using namespace std;

class PlayQueue
{
private:
    Node* front;
    Node* rear;

public:
    PlayQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(MediaItem* item)
    {
        Node* newNode = new Node(item);
        if (front == nullptr)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            newNode->prev = rear; 
            rear = newNode;
        }
        cout << "[OK] " << item->getTitle() << " added to the queue." << endl;
    }

    void playNext()
    {
        if (front == nullptr)
        {
            cout << "[X] Nothing in the queue." << endl;
            return;
        }

        Node* temp = front;
        cout << ">>> NOW PLAYING: ";
        temp->item->play();
        temp->item->incrementPlayCount();

        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
            cout << "Queue is now empty." << endl;
        }
        else
        {
            front->prev = nullptr;
            
            int count = 0;
            Node* curr = front;
            while (curr != nullptr) {
                count++;
                curr = curr->next;
            }
            cout << count << (count == 1 ? " track left in the queue." : " tracks left in the queue.") << endl;
        }

        delete temp;
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
            cout << index++ << ". " << current->item->getTitle() << endl;
            current = current->next;
        }
    }

    ~PlayQueue()
    {
        while (front != nullptr)
        {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

#endif