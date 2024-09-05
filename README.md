# Object-Oriented-Programming

This repository contains a collection of five C++ projects with graphical user interfaces, each designed to manage different data sets or provide interactive functionalities. Each application utilizes file handling for data persistence and is developed using the Qt framework for the GUI components.

## Table of Contents
1. [Library Management Application](#1-library-management-application)
2. [Product Management Application](#2-product-management-application)
3. [Song Management Application - Rank Based](#3-song-management-application---rank-based)
4. [Song Management Application - Genre Based](#4-song-management-application---genre-based)
5. [Programmers Task Management Application](#5-programmers-task-management-application)
6. [Tic-Tac-Toe Game Application](#6-tic-tac-toe-game-application)

---
## 1. Library Management Application

A C++ application with a graphical user interface to manage a collection of books in a library. The application supports typical CRUD operations on books and allows users to manage books in a shopping cart. Additional functionalities include sorting, filtering, undo/redo, and exporting cart data.

### Features:

- **Display Books**: Shows a list of books in a table format, sorted by title, author, or publication year.
- **Add Books**: Users can add new books to the library by providing the title, author, genre, and publication year.
- **Update Books**: Users can update the genre and publication year of existing books.
- **Delete Books**: Users can remove books from the library by selecting them based on title and author.
- **Search for Books**: Users can search for a specific book by title and author, displaying the details if found.

- **Sorting**:
  - **Sort by Title**: Sorts all books alphabetically by title.
  - **Sort by Author**: Sorts all books alphabetically by author.
  - **Sort by Year and Genre**: Sorts books based on the publication year and genre.

- **Filtering**:
  - **Filter by Title**: Filters the list of books by title.
  - **Filter by Year**: Filters the list of books by their publication year.

- **Cart Management**:
  - **Add to Cart**: Users can add books to a shopping cart.
  - **Empty Cart**: Users can empty the cart, removing all books.
  - **Generate Random Cart**: Generates a random selection of books for the cart.
  - **Cart CRUD GUI**: A separate window allows users to manage books in the cart.
  - **Cart Read-Only GUI**: Displays geometric shapes representing the number of books in the cart.

- **Undo/Redo Functionality**: 
  - **Undo**: Reverts the last operation (add, delete, update).
  - **Redo**: Reapplies the last undone operation.

- **Reports**:
  - **Generate Report**: Displays the number of books in the library, grouped by genre.

- **Export Cart**:
  - **Export Cart to CSV**: Users can export the cart contents to a CSV file.
  - **Export Cart to HTML**: Users can export the cart contents to an HTML file.


## 2. Product Management Application

A C++ application with a graphical user interface to manage a list of products, including functionalities for adding, deleting, and displaying products. The products are stored in a file and loaded on application startup.

### Features:
- **Display Products**: Shows a sorted list of products by price in a table.
- **Add Products**: Users can add new products with validation checks on input fields.
- **Filter Products**: Products can be filtered based on price using a slider.
- **Dynamic Windows**: Separate windows open for each product type, showing the count of products of that type.

---

## 3. Song Management Application - Rank Based

A C++ application for managing songs, focusing on ranking. The GUI allows users to sort, add, update, and delete songs, which are stored in a file.

### Features:
- **Display Songs**: Shows a list of songs sorted by rank.
- **Add and Update Songs**: Users can add new songs and update existing ones.
- **Delete Songs**: Songs can be deleted, with checks to prevent deletion of the last song by an artist.
- **Visual Ranking**: Displays a bar graph indicating the distribution of song ranks.

---

## 4. Song Management Application - Genre Based

A C++ application with a graphical interface for managing songs by genre. The application provides functionality to sort, add, and delete songs, focusing on genre-based operations.

### Features:
- **Display Songs**: Songs are displayed in a table sorted by the artist, with additional columns showing song count by the same artist and genre.
- **Add and Delete Songs**: Allows for adding and deleting songs from the list and file.
- **Visual Genre Representation**: Displays concentric circles representing the number of songs per genre.

---

## 5. Programmers Task Management Application

A C++ application for managing software development tasks, allowing users to assign tasks to programmers and track their progress.

### Features:
- **Display Tasks**: Shows tasks sorted by their status (open, in progress, closed).
- **Add and Search Tasks**: Users can add new tasks and search tasks by programmer.
- **Task Status Management**: Three additional windows for managing tasks by their status with buttons to change the status.

---

## 6. Tic-Tac-Toe Game Application

A C++ application implementing a multi-game Tic-Tac-Toe manager, allowing users to create and manage multiple games with different board sizes.

### Features:
- **Display Games**: Shows a list of all saved games sorted by status.
- **Create and Edit Games**: Users can create new games and modify existing games with validation checks.
- **Interactive Gameplay**: Supports ongoing games with real-time updates on the board and current player.

---
