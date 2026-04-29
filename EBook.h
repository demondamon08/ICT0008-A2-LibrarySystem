#ifndef EBOOK_H
#define EBOOK_H

#include <iostream>
#include <string>
#include "Book.h"
using namespace std;

class EBook : public Book {
private:
    string endOfLicenseDate;

public:
    EBook() : Book() {
        endOfLicenseDate = "";
    }

    void setEndOfLicenseDate(string date) {
        endOfLicenseDate = date;
    }

    string getEndOfLicenseDate() const {
        return endOfLicenseDate;
    }

    void displayBookDetails() const override {
        cout << "Type: E-Book" << endl;
        Book::displayBookDetails();
        cout << "End of License Date: " << endOfLicenseDate << endl;
        cout << "-----------------------------" << endl;
    }
};

#endif
