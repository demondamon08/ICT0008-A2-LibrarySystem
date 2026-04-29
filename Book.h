#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Author.h"
using namespace std;

class Book {
private:
    string title;
    string isbn;
    bool availability;
    string dateAdd;
    Author authors[2];
    int authorCount;

    bool valid;
    string errorMessage;

    bool isValidISBN(string i) const;

public:
    Book();
    Book(string t, string i, bool avail, string d, Author a[], int count);

    void setBookDetails(string t, string i, bool avail, string d, Author a[], int count);

    string getTitle() const;
    string getISBN() const;
    bool getAvailability() const;
    string getDateAdd() const;
    int getAuthorCount() const;
    Author getAuthor(int index) const;
    bool isValid() const;
    string getErrorMessage() const;

    virtual void displayBookDetails() const;
    bool borrowBook();
    void returnBook();
    virtual ~Book() {}
};

#endif