#ifndef HARDCOPYBOOK_H
#define HARDCOPYBOOK_H

#include <iostream>
#include <string>
#include "Book.h"
using namespace std;

class HardcopyBook : public Book {
private:
    string shelfNumber;

public:
    HardcopyBook() : Book() {
        shelfNumber = "";
    }

    void setShelfNumber(string shelf) {
        shelfNumber = shelf;
    }

    string getShelfNumber() const {
        return shelfNumber;
    }

    void displayBookDetails() const override {
        cout << "Type: Hardcopy" << endl;
        Book::displayBookDetails();
        cout << "Shelf Number: " << shelfNumber << endl;
        cout << "-----------------------------" << endl;
    }
};

#endif
