#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    bool available;

public:
    void setBookDetails(string t, string a, string i, bool status) {
        title = t;
        author = a;
        isbn = i;
        available = status;
    }

    void displayBookDetails() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Availability: " << (available ? "Available" : "Borrowed") << endl;
    }

    bool borrowBook() {
        if (available) {
            available = false;
            return true;
        }
        return false;
    }

    void returnBook() {
        available = true;
    }

    string getISBN() {
        return isbn;
    }
};

int main() {
    Book library[5];
    string searchISBN;
    bool found;

    // Initialize 5 books
    library[0].setBookDetails("The Great Gatsby", "F. Scott Fitzgerald", "1001", true);
    library[1].setBookDetails("To Kill a Mockingbird", "Harper Lee", "1002", true);
    library[2].setBookDetails("1984", "George Orwell", "1003", false);
    library[3].setBookDetails("Pride and Prejudice", "Jane Austen", "1004", true);
    library[4].setBookDetails("Moby Dick", "Herman Melville", "1005", true);

    cout << "=== Community Library System ===" << endl;

    while (true) {
        cout << "\nEnter ISBN to borrow a book (or 0 to exit): ";
        cin >> searchISBN;

        if (searchISBN == "0") {
            cout << "Program terminated." << endl;
            break;
        }

        found = false;

        for (int i = 0; i < 5; i++) {
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

    return 0;
}