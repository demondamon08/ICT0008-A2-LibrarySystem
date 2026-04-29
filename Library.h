#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"

class Library {
private:
    Book books[5];

public:
    void initializeBooks();
    void setBookAt(int index, Book book);
    Book getBookAt(int index) const;

    void displayAvailableBooks() const;
    int searchBookByISBN(string isbn) const;
    void borrowBookByISBN(string isbn);
};

#endif