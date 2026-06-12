# Student Management System (C++)

A console-based Student Management System built in **C++**, designed to efficiently manage student records using **file handling** and **menu-driven operations**.

 Overview

This project allows users to add, update, delete, search, sort, and display student records, with all data persistently stored in a local file (`students.dat`).

 Features

- **Add Student** — Add new records with duplicate ID validation
- **Display All** — View all records in a clean tabular format
- **Search by ID** — Quickly locate a specific student
- **Update Record** — Edit existing student details
- **Delete Record** — Remove a student record
- **Sort & Display** — Sort by Name, CGPA, or ID
- **Persistent Storage** — Data is saved to a file and reloaded automatically

Tech Stack

- **Language:** C++ (C++11)
- **Concepts Used:** File Handling (fstream), STL (vector, algorithm), Lambda Functions, Structs

How to Compile & Run

```bash
g++ -std=c++11 StudentManagementSystem.cpp -o sms
./sms
```

On Windows:
```bash
sms.exe
```

 File Structure

```
├── StudentManagementSystem.cpp   # Main source code
├── students.dat                  # Auto-generated data file (created on first run)
└── README.md                     # Project documentation
```

Sample Menu

```
╔══════════════════════════════╗
║  STUDENT MANAGEMENT SYSTEM    ║
╠══════════════════════════════╣
║  1. Add Student                ║
║  2. Display All                ║
║  3. Search by ID                ║
║  4. Update Record                ║
║  5. Delete Record                ║
║  6. Sort & Display                ║
║  0. Exit                          ║
╚══════════════════════════════╝
```

Expected Outcome

A functional application that allows users to add, update, delete, and display student information with persistent data storage for reliable record management.

Author

Developed as part of the Thiranex Internship Program.
