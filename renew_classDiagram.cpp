#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------- Author Class ----------------------
class Author {
private:
    string firstName;
    string lastName;

public:
    Author() {
        firstName = "";
        lastName = "";
    }

    Author(string fName, string lName) {
        firstName = fName;
        lastName = lName;
    }

    string getFullName() const {
        return firstName + " " + lastName;
    }
};

// ---------------------- Book Class (Base) ----------------------
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

    string getISBN() const {
        return ISBN;
    }

    bool isAvailable() const {
        return availability;
    }

    virtual ~Book() {}
};

// ---------------------- HardcopyBook Class ----------------------
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

    void displayBookDetails() const override {
        cout << "Type: Hardcopy" << endl;
        Book::displayBookDetails();
        cout << "Shelf Number: " << shelfNumber << endl;
        cout << "-----------------------------" << endl;
    }
};

// ---------------------- EBook Class ----------------------
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

    void displayBookDetails() const override {
        cout << "Type: E-Book" << endl;
        Book::displayBookDetails();
        cout << "End of License Date: " << endOfLicenseDate << endl;
        cout << "-----------------------------" << endl;
    }
};

// ---------------------- Library Class ----------------------
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

    void borrowBookByISBN(string ISBN) {
        int index = searchBookByISBN(ISBN);

        if (index == -1) {
            cout << "Error: Book not found." << endl;
            return;
        }

        if (books[index]->borrowBook()) {
            cout << "Book borrowed successfully." << endl;
            books[index]->displayBookDetails();
        } else {
            cout << "Error: Book is not available." << endl;
        }
    }
};

// ---------------------- Main Function ----------------------
int main() {
    Library library;
    string inputISBN;

    library.initializeBooks();

    cout << "=== Community Library System ===" << endl;

    while (true) {
        library.displayAvailableBooks();

        cout << "\nEnter ISBN to borrow a book (or 0 to end): ";
        cin >> inputISBN;

        if (inputISBN == "0") {
            cout << "Program ended." << endl;
            break;
        }

        library.borrowBookByISBN(inputISBN);
    }

    return 0;
}
