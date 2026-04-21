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

// ---------------------- User Class ----------------------
class User {
private:
    string userID;
    string name;
    string role;

public:
    User() {
        userID = "";
        name = "";
        role = "";
    }

    User(string id, string userName, string userRole) {
        userID = id;
        name = userName;
        role = userRole;
    }

    void displayUserDetails() const {
        cout << "\nUser Details" << endl;
        cout << "=============================" << endl;
        cout << "User ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Role: " << role << endl;
    }

    string getRole() const {
        return role;
    }
};

// ---------------------- Library Class ----------------------
class Library {
private:
    vector<Book> books;

public:
    void initializeBooks() {
        Book b1, b2, b3, b4, b5;

        b1.setBookDetails(
            "Clean Code",
            "1111",
            true,
            { Author("Robert", "Martin") }
        );

        b2.setBookDetails(
            "Design Patterns",
            "2222",
            true,
            {
                Author("Erich", "Gamma"),
                Author("Richard", "Helm"),
                Author("Ralph", "Johnson"),
                Author("John", "Vlissides")
            }
        );

        b3.setBookDetails(
            "The Pragmatic Programmer",
            "3333",
            true,
            {
                Author("Andrew", "Hunt"),
                Author("David", "Thomas")
            }
        );

        b4.setBookDetails(
            "Introduction to Algorithms",
            "4444",
            true,
            {
                Author("Thomas", "Cormen"),
                Author("Charles", "Leiserson"),
                Author("Ronald", "Rivest"),
                Author("Clifford", "Stein")
            }
        );

        b5.setBookDetails(
            "Refactoring",
            "5555",
            true,
            { Author("Martin", "Fowler") }
        );

        books.push_back(b1);
        books.push_back(b2);
        books.push_back(b3);
        books.push_back(b4);
        books.push_back(b5);
    }

    void displayAvailableBooks() const {
        cout << "\nAvailable Books" << endl;
        cout << "=============================" << endl;

        bool found = false;
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].isAvailable()) {
                books[i].displayBookDetails();
                found = true;
            }
        }

        if (!found) {
            cout << "No available books." << endl;
        }
    }

    void displayAllBooks() const {
        cout << "\nAll Books" << endl;
        cout << "=============================" << endl;

        if (books.empty()) {
            cout << "No books in the library." << endl;
            return;
        }

        for (size_t i = 0; i < books.size(); i++) {
            books[i].displayBookDetails();
        }
    }

    int searchBookByISBN(string ISBN) const {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getISBN() == ISBN) {
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

        if (books[index].borrowBook()) {
            cout << "Book borrowed successfully." << endl;
        } else {
            cout << "Error: Book is not available." << endl;
        }
    }

    void returnBookByISBN(string ISBN) {
        int index = searchBookByISBN(ISBN);

        if (index == -1) {
            cout << "Error: Book not found." << endl;
            return;
        }

        books[index].returnBook();
        cout << "Book returned successfully." << endl;
    }

    void addBook(Book book) {
        books.push_back(book);
        cout << "Book added successfully." << endl;
    }

    void removeBookByISBN(string ISBN) {
        int index = searchBookByISBN(ISBN);

        if (index == -1) {
            cout << "Error: Book not found." << endl;
            return;
        }

        books.erase(books.begin() + index);
        cout << "Book removed successfully." << endl;
    }
};

// ---------------------- Helper Function ----------------------
Book createBookFromInput() {
    string title, isbn;
    int authorCount;
    vector<Author> authors;

    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter ISBN: ";
    getline(cin, isbn);

    cout << "Enter number of authors: ";
    cin >> authorCount;
    cin.ignore();

    for (int i = 0; i < authorCount; i++) {
        string firstName, lastName;

        cout << "Enter first name of author " << i + 1 << ": ";
        getline(cin, firstName);

        cout << "Enter last name of author " << i + 1 << ": ";
        getline(cin, lastName);

        authors.push_back(Author(firstName, lastName));
    }

    Book newBook;
    newBook.setBookDetails(title, isbn, true, authors);
    return newBook;
}

// ---------------------- Main Function ----------------------
int main() {
    Library library;
    int roleChoice;
    int menuChoice;
    string isbn;

    library.initializeBooks();

    cout << "=== Community Library System Phase 2 ===" << endl;
    cout << "Select role:" << endl;
    cout << "1. Admin" << endl;
    cout << "2. User" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter choice: ";
    cin >> roleChoice;

    if (roleChoice == 0) {
        cout << "Program ended." << endl;
        return 0;
    }

    User currentUser;
    if (roleChoice == 1) {
        currentUser = User("A001", "Admin User", "Admin");
    } else if (roleChoice == 2) {
        currentUser = User("U001", "Library User", "User");
    } else {
        cout << "Invalid role selection." << endl;
        return 0;
    }

    currentUser.displayUserDetails();

    if (currentUser.getRole() == "Admin") {
        do {
            cout << "\n=== Admin Menu ===" << endl;
            cout << "1. Display all books" << endl;
            cout << "2. Add book" << endl;
            cout << "3. Remove book by ISBN" << endl;
            cout << "4. Search book by ISBN" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter choice: ";
            cin >> menuChoice;

            switch (menuChoice) {
                case 1:
                    library.displayAllBooks();
                    break;

                case 2: {
                    Book newBook = createBookFromInput();
                    library.addBook(newBook);
                    break;
                }

                case 3:
                    cout << "Enter ISBN to remove: ";
                    cin >> isbn;
                    library.removeBookByISBN(isbn);
                    break;

                case 4:
                    cout << "Enter ISBN to search: ";
                    cin >> isbn;
                    if (library.searchBookByISBN(isbn) != -1) {
                        cout << "Book found." << endl;
                    } else {
                        cout << "Book not found." << endl;
                    }
                    break;

                case 0:
                    cout << "Program ended." << endl;
                    break;

                default:
                    cout << "Invalid choice." << endl;
            }

        } while (menuChoice != 0);
    }
    else if (currentUser.getRole() == "User") {
        do {
            cout << "\n=== User Menu ===" << endl;
            cout << "1. Display available books" << endl;
            cout << "2. Search book by ISBN" << endl;
            cout << "3. Borrow book" << endl;
            cout << "4. Return book" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter choice: ";
            cin >> menuChoice;

            switch (menuChoice) {
                case 1:
                    library.displayAvailableBooks();
                    break;

                case 2:
                    cout << "Enter ISBN to search: ";
                    cin >> isbn;
                    if (library.searchBookByISBN(isbn) != -1) {
                        cout << "Book found." << endl;
                    } else {
                        cout << "Book not found." << endl;
                    }
                    break;

                case 3:
                    cout << "Enter ISBN to borrow: ";
                    cin >> isbn;
                    library.borrowBookByISBN(isbn);
                    break;

                case 4:
                    cout << "Enter ISBN to return: ";
                    cin >> isbn;
                    library.returnBookByISBN(isbn);
                    break;

                case 0:
                    cout << "Program ended." << endl;
                    break;

                default:
                    cout << "Invalid choice." << endl;
            }

        } while (menuChoice != 0);
    }

    return 0;
}1