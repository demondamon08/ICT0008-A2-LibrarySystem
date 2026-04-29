#include <iostream>
#include <cctype>
#include "Book.h"
using namespace std;

Book::Book() {
    title = "";
    isbn = "";
    availability = true;
    dateAdd = "";
    authorCount = 0;
    valid = false;
    errorMessage = "Book data is not initialized.";
}

Book::Book(string t, string i, bool avail, string d, Author a[], int count) {
    setBookDetails(t, i, avail, d, a, count);
}

bool Book::isValidISBN(string i) const {
    if (i.length() != 5) {
        return false;
    }

    bool hasLetter = false;
    bool hasDigit = false;

    for (int k = 0; k < i.length(); k++) {
        if (isalpha(i[k])) {
            hasLetter = true;
        } else if (isdigit(i[k])) {
            hasDigit = true;
        } else {
            return false;
        }
    }

    return hasLetter && hasDigit;
}

void Book::setBookDetails(string t, string i, bool avail, string d, Author a[], int count) {
    title = t;
    isbn = i;
    availability = avail;
    dateAdd = d;

    if (count > 2) {
        count = 2;
    }

    authorCount = count;
    for (int k = 0; k < authorCount; k++) {
        authors[k] = a[k];
    }

    valid = true;
    errorMessage = "";

    if (title == "") {
        valid = false;
        errorMessage = "Error: Title cannot be empty.";
        return;
    }

    if (!isValidISBN(isbn)) {
        valid = false;
        errorMessage = "Error: ISBN must be 5 characters and contain both letters and numbers.";
        return;
    }
}

string Book::getTitle() const {
    return title;
}

string Book::getISBN() const {
    return isbn;
}

bool Book::getAvailability() const {
    return availability;
}

string Book::getDateAdd() const {
    return dateAdd;
}

int Book::getAuthorCount() const {
    return authorCount;
}

Author Book::getAuthor(int index) const {
    return authors[index];
}

bool Book::isValid() const {
    return valid;
}

string Book::getErrorMessage() const {
    return errorMessage;
}

void Book::displayBookDetails() const {
    if (!valid) {
        cout << errorMessage << endl;
        cout << "Title: " << title << endl;

        cout << "Author: ";
        if (authorCount == 0) {
            cout << "Unknown Author";
        } else {
            for (int k = 0; k < authorCount; k++) {
                cout << authors[k].getFullName();
                if (k < authorCount - 1) {
                    cout << ", ";
                }
            }
        }
        cout << endl;

        cout << "ISBN: " << isbn << endl;
        cout << "Availability: " << (availability ? "Available" : "Borrowed") << endl;
        cout << "DateAdd: " << dateAdd << endl;
        return;
    }

    cout << "Title: " << title << endl;

    cout << "Author: ";
    if (authorCount == 0) {
        cout << "Unknown Author";
    } else {
        for (int k = 0; k < authorCount; k++) {
            cout << authors[k].getFullName();
            if (k < authorCount - 1) {
                cout << ", ";
            }
        }
    }
    cout << endl;

    cout << "ISBN: " << isbn << endl;
    cout << "Availability: " << (availability ? "Available" : "Borrowed") << endl;
    cout << "DateAdd: " << dateAdd << endl;
}

bool Book::borrowBook() {
    if (!valid) {
        return false;
    }

    if (availability) {
        availability = false;
        return true;
    }
    return false;
}

void Book::returnBook() {
    if (valid) {
        availability = true;
    }
}