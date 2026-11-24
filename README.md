# Library Management System

A library management system developed in C as part of the Data Structures course. The project uses AVL trees and doubly linked lists to manage books, users, and loans.

## Features

- Book registration, search, update, and deletion.
- User registration, search, update, and deletion.
- Book lending and return management.
- Loan renewal.
- Date validation and overdue checking.
- Automatic AVL tree balancing.

## Data Structures

- **AVL Trees:** Used to store books and users, maintaining balance after insertion and deletion operations.
- **Doubly Linked Lists:** Used to manage loan records and relationships between books and users.
- **Dynamic Memory Allocation:** Used for the creation and management of data structures.

## Technologies

- C
- GCC
- AVL Trees
- Doubly Linked Lists

## Compilation

Compile the project using GCC:

```bash
gcc work.c -o library
```

## Execution

Run the compiled program:

```bash
./library
```

## Project Structure

| File | Description |
|---|---|
| `work.c` | Main program and menu operations |
| `AVL_B.h` | AVL tree operations for books |
| `AVL_U.h` | AVL tree operations for users |
| `listEnB.h` | Doubly linked list operations associated with books |
| `listEnU.h` | Doubly linked list operations associated with users |
| `TAD.h` | Auxiliary functions and date management |
| `test.txt` | Book data used for testing |
| `usuarios.txt` | User data used for testing |

## Academic Project

Developed as part of the Data Structures course, focusing on the implementation of AVL trees, doubly linked lists, dynamic memory allocation, and the relationship between data structures.
