#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <vector>
#include "Author.h"
using namespace std;

class Book {
private:
    string title;
    string ISBN;
    bool availability;
    vector<Author> authors;

public:
    Book() {
        title = "";
        ISBN = "";
        availability = true;
    }

    void setBookDetails(string bookTitle, string bookISBN, bool status, vector<Author> bookAuthors) {
        title = bookTitle;
        ISBN = bookISBN;
        availability = status;
        authors = bookAuthors;
    }

    virtual void displayBookDetails() const {
        cout << "Title: " << title << endl;
        cout << "Author(s): ";
        for (size_t i = 0; i < authors.size(); i++) {
            cout << authors[i].getFullName();
            if (i < authors.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Availability: " << (availability ? "Available" : "Borrowed") << endl;
    }

    bool borrowBook() {
        if (availability) {
            availability = false;
            return true;
        }
        return false;
    }

    void returnBook() {
        availability = true;
    }

    string getTitle() const { return title; }
    string getISBN() const { return ISBN; }
    bool isAvailable() const { return availability; }

    virtual ~Book() {}
};

#endif
