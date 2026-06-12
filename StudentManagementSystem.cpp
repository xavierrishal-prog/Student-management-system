/*
 * ╔══════════════════════════════════════════════════════════╗
 * ║        STUDENT MANAGEMENT SYSTEM  — C++                 ║
 * ║        File Handling + Menu-Driven Operations            ║
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

// ─── Constants ────────────────────────────────────────────
const string FILE_NAME = "students.dat";
const string DIVIDER   = string(58, '─');

// ─── Student Structure ────────────────────────────────────
struct Student {
    int    id;
    string name;
    string branch;
    float  cgpa;
    string email;

    // Serialize to CSV line
    string serialize() const {
        ostringstream oss;
        oss << id << "," << name << "," << branch << ","
            << fixed << setprecision(2) << cgpa << "," << email;
        return oss.str();
    }

    // Deserialize from CSV line
    static Student deserialize(const string& line) {
        Student s;
        istringstream iss(line);
        string token;

        getline(iss, token, ','); s.id     = stoi(token);
        getline(iss, token, ','); s.name   = token;
        getline(iss, token, ','); s.branch = token;
        getline(iss, token, ','); s.cgpa   = stof(token);
        getline(iss, token, ','); s.email  = token;

        return s;
    }
};

// ─── Utility: Clear Input Buffer ─────────────────────────
void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ─── Utility: Print Table Row ────────────────────────────
void printRow(const Student& s) {
    cout << "│ " << left
         << setw(5)  << s.id
         << setw(20) << s.name
         << setw(10) << s.branch
         << setw(6)  << fixed << setprecision(2) << s.cgpa
         << setw(25) << s.email
         << " │\n";
}

void printTableHeader() {
    cout << "\n┌" << string(58, '─') << "┐\n";
    cout << "│ " << left
         << setw(5)  << "ID"
         << setw(20) << "Name"
         << setw(10) << "Branch"
         << setw(6)  << "CGPA"
         << setw(25) << "Email"
         << " │\n";
    cout << "├" << string(58, '─') << "┤\n";
}

void printTableFooter() {
    cout << "└" << string(58, '─') << "┘\n";
}

// ─── File Operations ─────────────────────────────────────

// Load all students from file
vector<Student> loadAll() {
    vector<Student> students;
    ifstream fin(FILE_NAME);
    string line;
    while (getline(fin, line)) {
        if (!line.empty())
            students.push_back(Student::deserialize(line));
    }
    return students;
}

// Save all students to file (overwrite)
void saveAll(const vector<Student>& students) {
    ofstream fout(FILE_NAME, ios::trunc);
    for (const auto& s : students)
        fout << s.serialize() << "\n";
}

// Check if ID already exists
bool idExists(const vector<Student>& students, int id) {
    return any_of(students.begin(), students.end(),
                  [id](const Student& s) { return s.id == id; });
}

// ─── CRUD Operations ─────────────────────────────────────

void addStudent() {
    Student s;
    auto students = loadAll();

    cout << "\n  ── Add New Student ──\n";
    cout << "  Enter ID     : "; cin >> s.id;
    if (idExists(students, s.id)) {
        cout << "  ✘ ID already exists!\n";
        return;
    }
    clearInput();
    cout << "  Enter Name   : "; getline(cin, s.name);
    cout << "  Enter Branch : "; getline(cin, s.branch);
    cout << "  Enter CGPA   : "; cin >> s.cgpa;
    clearInput();
    cout << "  Enter Email  : "; getline(cin, s.email);

    students.push_back(s);
    saveAll(students);
    cout << "  ✔ Student added successfully!\n";
}

void displayAll() {
    auto students = loadAll();
    if (students.empty()) {
        cout << "\n  No records found.\n";
        return;
    }
    printTableHeader();
    for (const auto& s : students)
        printRow(s);
    printTableFooter();
    cout << "  Total: " << students.size() << " student(s)\n";
}

void searchStudent() {
    int id;
    cout << "\n  Enter Student ID to search: "; cin >> id;
    auto students = loadAll();

    auto it = find_if(students.begin(), students.end(),
                      [id](const Student& s) { return s.id == id; });

    if (it == students.end()) {
        cout << "  ✘ Student not found.\n";
        return;
    }
    printTableHeader();
    printRow(*it);
    printTableFooter();
}

void updateStudent() {
    int id;
    cout << "\n  Enter Student ID to update: "; cin >> id;
    auto students = loadAll();

    auto it = find_if(students.begin(), students.end(),
                      [id](const Student& s) { return s.id == id; });

    if (it == students.end()) {
        cout << "  ✘ Student not found.\n";
        return;
    }

    clearInput();
    cout << "  New Name   [" << it->name   << "]: "; getline(cin, it->name);
    cout << "  New Branch [" << it->branch << "]: "; getline(cin, it->branch);
    cout << "  New CGPA   [" << it->cgpa   << "]: "; cin >> it->cgpa;
    clearInput();
    cout << "  New Email  [" << it->email  << "]: "; getline(cin, it->email);

    saveAll(students);
    cout << "  ✔ Record updated successfully!\n";
}

void deleteStudent() {
    int id;
    cout << "\n  Enter Student ID to delete: "; cin >> id;
    auto students = loadAll();

    auto before = students.size();
    students.erase(remove_if(students.begin(), students.end(),
                             [id](const Student& s) { return s.id == id; }),
                   students.end());

    if (students.size() == before) {
        cout << "  ✘ Student not found.\n";
        return;
    }
    saveAll(students);
    cout << "  ✔ Student deleted successfully!\n";
}

void sortAndDisplay() {
    auto students = loadAll();
    if (students.empty()) { cout << "\n  No records found.\n"; return; }

    cout << "\n  Sort by: 1) Name  2) CGPA  3) ID\n  Choice: ";
    int choice; cin >> choice;

    if (choice == 1)
        sort(students.begin(), students.end(),
             [](const Student& a, const Student& b) { return a.name < b.name; });
    else if (choice == 2)
        sort(students.begin(), students.end(),
             [](const Student& a, const Student& b) { return a.cgpa > b.cgpa; });
    else
        sort(students.begin(), students.end(),
             [](const Student& a, const Student& b) { return a.id < b.id; });

    printTableHeader();
    for (const auto& s : students)
        printRow(s);
    printTableFooter();
}

// ─── Menu ─────────────────────────────────────────────────
void showMenu() {
    cout << "\n╔══════════════════════════════╗\n";
    cout << "║  STUDENT MANAGEMENT SYSTEM   ║\n";
    cout << "╠══════════════════════════════╣\n";
    cout << "║  1. Add Student              ║\n";
    cout << "║  2. Display All              ║\n";
    cout << "║  3. Search by ID             ║\n";
    cout << "║  4. Update Record            ║\n";
    cout << "║  5. Delete Record            ║\n";
    cout << "║  6. Sort & Display           ║\n";
    cout << "║  0. Exit                     ║\n";
    cout << "╚══════════════════════════════╝\n";
    cout << "  Choice: ";
}

// ─── Main ─────────────────────────────────────────────────
int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1: addStudent();    break;
            case 2: displayAll();   break;
            case 3: searchStudent();break;
            case 4: updateStudent();break;
            case 5: deleteStudent();break;
            case 6: sortAndDisplay();break;
            case 0: cout << "\n  Goodbye!\n"; break;
            default: cout << "  Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
