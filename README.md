# Object-Oriented-Programming

This repository contains a collection of five C++ projects with graphical user interfaces, each designed to manage different data sets or provide interactive functionalities. Each application utilizes file handling for data persistence and is developed using the Qt framework for the GUI components.

## Table of Contents

1. [Product Management Application](#1-product-management-application)
2. [Song Management Application - Rank Based](#2-song-management-application---rank-based)
3. [Song Management Application - Genre Based](#3-song-management-application---genre-based)
4. [Programmers Task Management Application](#4-programmers-task-management-application)
5. [Tic-Tac-Toe Game Application](#5-tic-tac-toe-game-application)

---

## 1. Product Management Application

A C++ application with a graphical user interface to manage a list of products, including functionalities for adding, deleting, and displaying products. The products are stored in a file and loaded on application startup.

### Features:
- **Display Products**: Shows a sorted list of products by price in a table.
- **Add Products**: Users can add new products with validation checks on input fields.
- **Filter Products**: Products can be filtered based on price using a slider.
- **Dynamic Windows**: Separate windows open for each product type, showing the count of products of that type.

---

## 2. Song Management Application - Rank Based

A C++ application for managing songs, focusing on ranking. The GUI allows users to sort, add, update, and delete songs, which are stored in a file.

### Features:
- **Display Songs**: Shows a list of songs sorted by rank.
- **Add and Update Songs**: Users can add new songs and update existing ones.
- **Delete Songs**: Songs can be deleted, with checks to prevent deletion of the last song by an artist.
- **Visual Ranking**: Displays a bar graph indicating the distribution of song ranks.

---

## 3. Song Management Application - Genre Based

A C++ application with a graphical interface for managing songs by genre. The application provides functionality to sort, add, and delete songs, focusing on genre-based operations.

### Features:
- **Display Songs**: Songs are displayed in a table sorted by the artist, with additional columns showing song count by the same artist and genre.
- **Add and Delete Songs**: Allows for adding and deleting songs from the list and file.
- **Visual Genre Representation**: Displays concentric circles representing the number of songs per genre.

---

## 4. Programmers Task Management Application

A C++ application for managing software development tasks, allowing users to assign tasks to programmers and track their progress.

### Features:
- **Display Tasks**: Shows tasks sorted by their status (open, in progress, closed).
- **Add and Search Tasks**: Users can add new tasks and search tasks by programmer.
- **Task Status Management**: Three additional windows for managing tasks by their status with buttons to change the status.

---

## 5. Tic-Tac-Toe Game Application

A C++ application implementing a multi-game Tic-Tac-Toe manager, allowing users to create and manage multiple games with different board sizes.

### Features:
- **Display Games**: Shows a list of all saved games sorted by status.
- **Create and Edit Games**: Users can create new games and modify existing games with validation checks.
- **Interactive Gameplay**: Supports ongoing games with real-time updates on the board and current player.

---
