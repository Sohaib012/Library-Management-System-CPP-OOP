# ibrary-system-cpp-oop

## Problem Statement
The project aims to develop a reliable Library Management System using C++ and Object-Oriented Programming principles. The algorithm searches for books, reserves them, and displays relevant information if the book is available. Users can also search for books by title or author's surname.

## Introduction
The Library Management System allows users to perform functions such as reserving and returning books. Object-Oriented Programming principles like inheritance, operator overloading, friend classes, and polymorphism are employed. File handling is crucial for permanent data storage about books and reservations.

### Program Structure
The program consists of:
- `Main.cpp`
- `Classes.h` (header file with classes: Book, Library, Reserve, Student, and related functions)

### Required Files
The program utilizes two files for its functions:
1. **Library.csv:**
   - Contains book information (book name, author's first name, author's surname, and remaining copies).
   - Records are stored in the format: (S/No., book name, author’s 1st name, author’s surname, copies remaining)

2. **Reserve.csv:**
   - Includes registration number, reserved book name, and author's information.

