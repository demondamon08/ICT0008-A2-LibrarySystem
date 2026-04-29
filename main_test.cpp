// g++ -std=c++17 -o main_test Author.cpp Book.cpp Sort.cpp main_test.cpp

#include <iostream>
#include "Author.h"
#include "Book.h"
#include "HardcopyBook.h"
#include "EBook.h"
#include "Sort.h"
using namespace std;

void displayArray(Book books[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "\nBook " << i + 1 << endl;
        books[i].displayBookDetails();
    }
}

int main() {

    // ============================================================
    // HardcopyBook — Correct Initialization
    // ============================================================
    cout << "=== Correct HardcopyBook ===" << endl;

    Author hbA1[1] = { Author("John", "Smith") };
    HardcopyBook hb1;
    hb1.setBookDetails("C++ Basics", "A1234", true, "2026-04-21", hbA1, 1);
    hb1.setShelfNumber("S1");
    hb1.displayBookDetails();

    Author hbA2[2] = { Author("Mark", ""), Author("Jane", "Taylor") };
    HardcopyBook hb2;
    hb2.setBookDetails("Programming Logic", "C3456", true, "2026-04-15", hbA2, 2);
    hb2.setShelfNumber("S3");
    hb2.displayBookDetails();

    // ============================================================
    // EBook — Correct Initialization
    // ============================================================
    cout << "=== Correct EBook ===" << endl;

    Author ebA1[1] = { Author("Anna", "Lee") };
    EBook eb1;
    eb1.setBookDetails("Data Structures", "B2345", false, "2026-04-18", ebA1, 1);
    eb1.setEndOfLicenseDate("2027-01-01");
    eb1.displayBookDetails();

    // ============================================================
    // Incorrect Books (invalid data — Book validates on setBookDetails)
    // ============================================================
    cout << "=== Incorrect Books ===" << endl;

    Author badA1[1] = { Author("John", "") };
    HardcopyBook wrong1;
    wrong1.setBookDetails("", "A1111", true, "2026-04-01", badA1, 1);  // empty title
    wrong1.setShelfNumber("X1");
    wrong1.displayBookDetails();
    cout << "[NOTE] Title is empty — title must not be empty." << endl << endl;

    Author badA2[1] = { Author("OnlyName", "") };
    EBook wrong2;
    wrong2.setBookDetails("Network", "12345", false, "2026-04-02", badA2, 1);  // ISBN starts with digit
    wrong2.setEndOfLicenseDate("2027-01-01");
    wrong2.displayBookDetails();
    cout << "[NOTE] ISBN '" << wrong2.getISBN() << "' does not start with a letter — must be 1 letter + 4 digits." << endl << endl;

    Author badA3[1] = { Author("", "Surname") };
    HardcopyBook wrong3;
    wrong3.setBookDetails("Database", "AB@12", true, "2026-04-03", badA3, 1);  // ISBN has special char
    wrong3.setShelfNumber("X3");
    wrong3.displayBookDetails();
    cout << "[NOTE] ISBN '" << wrong3.getISBN() << "' contains invalid character '@'." << endl << endl;

    // ============================================================
    // Sort — 3 arrays in different order, sorted by ISBN
    // ============================================================
    Author sa1[1] = { Author("John", "Smith") };
    Author sa2[1] = { Author("Anna", "Lee") };
    Author sa3[1] = { Author("Mark", "Brown") };

    Book ascending[3] = {
        Book("Book A", "A1234", true,  "2026-04-01", sa1, 1),
        Book("Book B", "B2345", true,  "2026-04-02", sa2, 1),
        Book("Book C", "C3456", false, "2026-04-03", sa3, 1)
    };

    Book descending[3] = {
        Book("Book C", "C3456", false, "2026-04-03", sa3, 1),
        Book("Book B", "B2345", true,  "2026-04-02", sa2, 1),
        Book("Book A", "A1234", true,  "2026-04-01", sa1, 1)
    };

    Book mixed[3] = {
        Book("Book B", "B2345", true,  "2026-04-02", sa2, 1),
        Book("Book C", "C3456", false, "2026-04-03", sa3, 1),
        Book("Book A", "A1234", true,  "2026-04-01", sa1, 1)
    };

    cout << "\n=== Ascending order before sort ===" << endl;
    displayArray(ascending, 3);
    sortBooksByISBN(ascending, 3);
    cout << "\n=== Ascending order after sort ===" << endl;
    displayArray(ascending, 3);

    cout << "\n\n=== Descending order before sort ===" << endl;
    displayArray(descending, 3);
    sortBooksByISBN(descending, 3);
    cout << "\n=== Descending order after sort ===" << endl;
    displayArray(descending, 3);

    cout << "\n\n=== Mixed order before sort ===" << endl;
    displayArray(mixed, 3);
    sortBooksByISBN(mixed, 3);
    cout << "\n=== Mixed order after sort ===" << endl;
    displayArray(mixed, 3);

    return 0;
}
