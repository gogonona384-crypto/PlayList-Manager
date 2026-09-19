# Playlist Manager Application

A C++ Object-Oriented application for managing dynamic playlists, searching items, sorting, and maintaining a playback queue.

## Features
- **Library Management**: Add, delete, and view media items (Songs & Podcasts).
- **Playback Queue**: Enqueue and play dynamic tracks using custom Queue logic.
- **Search & Sort**: Linear search by title/artist and selection sort by title.
- **Statistics**: Display library overview and total durations.

## Big O Complexity Analysis

| Operation | Function / Method | Time Complexity | Complexity Reasoning |
| :--- | :--- | :--- | :--- |
| **Search** | `searchItem()` | O(N)| Performs linear search scanning elements up to $N$. |
| **Sort** | `sortLibrary()` | O(N^2) | Selection Sort algorithm utilizing nested loops. |
| **Enqueue** | `enqueue()` | O(1) | Direct insertion at the rear of the Queue. |
| **Stats** | `showStats()` | O(N)| Single traversal over vector items to aggregate statistics. |

## How to Run
1. Compile the program:
   `cl.exe /EHsc src/main.cpp /Fe:src/main.exe`
2. Run executable:
   `.\src\main.exe`
## UML Class Diagram
![UML Diagram](docs/uml-class-diagram.png)
## Program Screenshots
![App Execution](docs/screenshot.png)
