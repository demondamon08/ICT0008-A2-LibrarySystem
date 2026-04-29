#include <iostream>
#include "Library.h"
using namespace std;

void Library::initializeBooks() {
    for (int i = 0; i < 5; i++) {
        books[i] = Book();
    }
}

void Library::setBookAt(int index, Book book) {
    if (index >= 0 && index < 5) {
        books[index] = book;
    }
}

Book Library::getBookAt(int index) const {
    return books[index];
}

void Library::displayAvailableBooks() const {
    for (int i = 0; i < 5; i++) {
        if (books[i].getAvailability()) {
            books[i].displayBookDetails();
            cout << endl;
        }
    }
}

int Library::searchBookByISBN(string isbn) const {
    for (int i = 0; i < 5; i++) {
        if (books[i].getISBN() == isbn) {
            return i;
        }
    }
    return -1;
}

void Library::borrowBookByISBN(string isbn) {
    int index = searchBookByISBN(isbn);

    if (index == -1) {
        cout << "Book not found." << endl;
    } else {
        if (books[index].borrowBook()) {
            cout << "Book borrowed successfully." << endl;
        } else {
            cout << "Book is not available." << endl;
        }
    }
}