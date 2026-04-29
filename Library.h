#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include <vector>
#include "Author.h"
#include "HardcopyBook.h"
#include "EBook.h"
using namespace std;

class Library {
private:
    vector<Book*> books;

public:
    ~Library() {
        for (size_t i = 0; i < books.size(); i++) {
            delete books[i];
        }
        books.clear();
    }

    void initializeBooks() {
        HardcopyBook* b1 = new HardcopyBook();
        b1->setBookDetails("Clean Code", "1111", true, { Author("Robert", "Martin") });
        b1->setShelfNumber("A1");
        books.push_back(b1);

        HardcopyBook* b2 = new HardcopyBook();
        b2->setBookDetails("Design Patterns", "2222", true, {
            Author("Erich", "Gamma"), Author("Richard", "Helm"),
            Author("Ralph", "Johnson"), Author("John", "Vlissides")
        });
        b2->setShelfNumber("A2");
        books.push_back(b2);

        HardcopyBook* b3 = new HardcopyBook();
        b3->setBookDetails("The Pragmatic Programmer", "3333", true, {
            Author("Andrew", "Hunt"), Author("David", "Thomas")
        });
        b3->setShelfNumber("B1");
        books.push_back(b3);

        EBook* b4 = new EBook();
        b4->setBookDetails("Introduction to Algorithms", "4444", true, {
            Author("Thomas", "Cormen"), Author("Charles", "Leiserson"),
            Author("Ronald", "Rivest"), Author("Clifford", "Stein")
        });
        b4->setEndOfLicenseDate("2025-12-31");
        books.push_back(b4);

        EBook* b5 = new EBook();
        b5->setBookDetails("Refactoring", "5555", true, { Author("Martin", "Fowler") });
        b5->setEndOfLicenseDate("2026-06-30");
        books.push_back(b5);
    }

    void displayAvailableBooks() const {
        cout << "\nAvailable Books" << endl;
        cout << "=============================" << endl;
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i]->isAvailable()) {
                books[i]->displayBookDetails();
            }
        }
    }

    int searchBookByISBN(string ISBN) const {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i]->getISBN() == ISBN) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    bool borrowBookByISBN(string ISBN) {
        int index = searchBookByISBN(ISBN);
        if (index == -1) return false;
        return books[index]->borrowBook();
    }

    bool returnBookByISBN(string ISBN) {
        int index = searchBookByISBN(ISBN);
        if (index == -1) return false;
        books[index]->returnBook();
        return true;
    }

    bool isBookAvailable(string ISBN) const {
        int index = searchBookByISBN(ISBN);
        if (index == -1) return false;
        return books[index]->isAvailable();
    }
};

#endif
