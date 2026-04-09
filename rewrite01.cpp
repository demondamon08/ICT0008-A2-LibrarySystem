#include <iostream>
#include <string>
using namespace std;

// ---------- Book class ----------
class Book {
private:
    string title;
    string author;
    string ISBN;
    bool availability;

public:
    // Set book details
    void setBookDetails(string t, string a, string i, bool status) {
        title = t;
        author = a;
        ISBN = i;
        availability = status;
    }

    // Display book details
    void displayBookDetails() {
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "ISBN: " << ISBN << "\n";
        cout << "Availability: ";
        if (availability) {
            cout << "Available\n";
        } else {
            cout << "Borrowed\n";
        }
        cout << "-------------------------\n";
    }

    // Check availability
    bool isAvailable() {
        return availability;
    }

    // Borrow book
    bool borrowBook() {
        if (availability) {
            availability = false;
            return true;
        }
        return false;
    }

    // Return book
    void returnBook() {
        availability = true;
    }

    // Get ISBN
    string getISBN() {
        return ISBN;
    }
};

// ---------- Search function ----------
int findBookByISBN(Book books[], int size, string searchISBN) {
    for (int i = 0; i < size; i++) {
        if (books[i].getISBN() == searchISBN) {
            return i;
        }
    }
    return -1;
}

// ---------- Main program ----------
int main() {
    Book books[5];

    // Initialize 5 books
    books[0].setBookDetails("The Great Gatsby", "F. Scott Fitzgerald", "1001", true);
    books[1].setBookDetails("To Kill a Mockingbird", "Harper Lee", "1002", true);
    books[2].setBookDetails("1984", "George Orwell", "1003", false);
    books[3].setBookDetails("Pride and Prejudice", "Jane Austen", "1004", true);
    books[4].setBookDetails("Moby Dick", "Herman Melville", "1005", true);

    cout << "=== Library Book Management System ===\n";

    while (true) {
        cout << "\nAvailable books in the library:\n";
        cout << "-------------------------\n";

        for (int i = 0; i < 5; i++) {
            books[i].displayBookDetails();
        }

        cout << "Enter ISBN to borrow a book (or 0 to exit): ";
        string inputISBN;
        getline(cin, inputISBN);

        // Exit condition
        if (inputISBN == "0") {
            cout << "Program ended.\n";
            break;
        }

        // Search matching ISBN
        int index = findBookByISBN(books, 5, inputISBN);

        if (index == -1) {
            cout << "Book not found.\n";
        } else {
            if (books[index].borrowBook()) {
                cout << "Book borrowed successfully.\n";
            } else {
                cout << "Book is unavailable.\n";
            }
        }
    }

    return 0;
}