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

// ---------------------- Book Class ----------------------
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

    void displayBookDetails() const {
        cout << "Title: " << title << endl;
        cout << "ISBN: " << ISBN << endl;

        cout << "Author(s): ";
        for (size_t i = 0; i < authors.size(); i++) {
            cout << authors[i].getFullName();
            if (i < authors.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;

        cout << "Availability: " << (availability ? "Available" : "Borrowed") << endl;
        cout << "-----------------------------" << endl;
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
};

// ---------------------- Library Class ----------------------
class Library {
private:
    Book books[5];

public:
    void initializeBooks() {
        books[0].setBookDetails(
            "Clean Code",
            "1111",
            true,
            { Author("Robert", "Martin") }
        );

        books[1].setBookDetails(
            "Design Patterns",
            "2222",
            true,
            { Author("Erich", "Gamma"), Author("Richard", "Helm"),
              Author("Ralph", "Johnson"), Author("John", "Vlissides") }
        );

        books[2].setBookDetails(
            "The Pragmatic Programmer",
            "3333",
            true,
            { Author("Andrew", "Hunt"), Author("David", "Thomas") }
        );

        books[3].setBookDetails(
            "Introduction to Algorithms",
            "4444",
            true,
            { Author("Thomas", "Cormen"), Author("Charles", "Leiserson"),
              Author("Ronald", "Rivest"), Author("Clifford", "Stein") }
        );

        books[4].setBookDetails(
            "Refactoring",
            "5555",
            true,
            { Author("Martin", "Fowler") }
        );
    }

    void displayAvailableBooks() const {
        cout << "\nAvailable Books" << endl;
        cout << "=============================" << endl;

        for (int i = 0; i < 5; i++) {
            if (books[i].isAvailable()) {
                books[i].displayBookDetails();
            }
        }
    }

    int searchBookByISBN(string ISBN) const {
        for (int i = 0; i < 5; i++) {
            if (books[i].getISBN() == ISBN) {
                return i;
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

        if (books[index].borrowBook()) {
            cout << "Book borrowed successfully." << endl;
            books[index].displayBookDetails();
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