#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    string ISBN;
    bool availability;

public:
    void setBookDetails(string t, string a, string i, bool status) {
        title = t;
        author = a;
        ISBN = i;
        availability = status;
    }

    void displayBookDetails() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Availability: " << (availability ? "Available" : "Borrowed") << endl;
        cout << "--------------------------" << endl;
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

    string getISBN() {
        return ISBN;
    }

    bool isEmpty() {
        return ISBN == "";
    }
};

// ---------- Add new book ----------
bool addBook(Book library[], int size, int& count) {
    if (count >= size) {
        cout << "Library is full. Cannot add more books." << endl;
        return false;
    }

    string title, author, ISBN;

    cout << "\n=== Add New Book ===" << endl;
    cout << "Enter title: ";
    getline(cin, title);

    cout << "Enter author: ";
    getline(cin, author);

    cout << "Enter ISBN: ";
    getline(cin, ISBN);

    // check duplicate ISBN
    for (int i = 0; i < count; i++) {
        if (library[i].getISBN() == ISBN) {
            cout << "Error: ISBN already exists." << endl;
            return false;
        }
    }

    library[count].setBookDetails(title, author, ISBN, true);
    count++;

    cout << "Book added successfully." << endl;
    return true;
}

// ---------- Search and borrow ----------
void borrowByISBN(Book library[], int count) {
    string searchISBN;
    bool found = false;

    cout << "\nEnter ISBN to borrow a book (or 0 to exit): ";
    getline(cin, searchISBN);

    if (searchISBN == "0") {
        cout << "Returning to main menu..." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        if (library[i].getISBN() == searchISBN) {
            found = true;
            cout << "\nBook found:" << endl;
            library[i].displayBookDetails();

            if (library[i].borrowBook()) {
                cout << "Book borrowed successfully." << endl;
            } else {
                cout << "Error: This book is currently unavailable." << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "Error: Book with ISBN " << searchISBN << " not found." << endl;
    }
}

// ---------- Show all books ----------
void showAllBooks(Book library[], int count) {
    cout << "\n=== Book List ===" << endl;

    if (count == 0) {
        cout << "No books in the library." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        library[i].displayBookDetails();
    }
}

// ---------- Main program ----------
int main() {
    const int MAX_BOOKS = 10;
    Book library[MAX_BOOKS];
    int bookCount = 5;
    string choice;

    // Initialize books
    library[0].setBookDetails("The Great Gatsby", "F. Scott Fitzgerald", "1001", true);
    library[1].setBookDetails("To Kill a Mockingbird", "Harper Lee", "1002", true);
    library[2].setBookDetails("1984", "George Orwell", "1003", false);
    library[3].setBookDetails("Pride and Prejudice", "Jane Austen", "1004", true);
    library[4].setBookDetails("Moby Dick", "Herman Melville", "1005", true);

    cout << "=== Community Library System ===" << endl;

    while (true) {
        cout << "\nSelect role:" << endl;
        cout << "1. Library" << endl;
        cout << "2. User" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        getline(cin, choice);

        if (choice == "0") {
            cout << "Program terminated." << endl;
            break;
        }
        else if (choice == "1") {
            string libraryChoice;

            cout << "\n=== Library Menu ===" << endl;
            cout << "1. Add book" << endl;
            cout << "2. Show all books" << endl;
            cout << "0. Back" << endl;
            cout << "Enter choice: ";
            getline(cin, libraryChoice);

            if (libraryChoice == "1") {
                addBook(library, MAX_BOOKS, bookCount);
            }
            else if (libraryChoice == "2") {
                showAllBooks(library, bookCount);
            }
            else if (libraryChoice == "0") {
                continue;
            }
            else {
                cout << "Invalid choice." << endl;
            }
        }
        else if (choice == "2") {
            borrowByISBN(library, bookCount);
        }
        else {
            cout << "Invalid choice. Please select 0, 1, or 2." << endl;
        }
    }

    return 0;
}