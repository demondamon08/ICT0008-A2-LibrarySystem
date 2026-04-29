// Standalone test file — no external headers required
// Compile: g++ -std=c++17 -o test main_test_standalone.cpp && ./test

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ============================================================
// Author
// ============================================================
class Author {
private:
    string firstName;
    string lastName;
public:
    Author() : firstName(""), lastName("") {}
    Author(string fName, string lName) : firstName(fName), lastName(lName) {}

    void setAuthorDetails(string fName, string lName) {
        firstName = fName;
        lastName = lName;
    }

    string getFirstName() const { return firstName; }
    string getLastName()  const { return lastName; }

    string getFullName() const {
        if (firstName != "" && lastName != "") return firstName + " " + lastName;
        if (firstName != "") return firstName;
        if (lastName  != "") return lastName;
        return "Unknown Author";
    }
};

// ============================================================
// Book (base class)
// ============================================================
class Book {
private:
    string title;
    string isbn;
    bool   availability;
    string dateAdd;
    Author authors[2];
    int    authorCount;
    bool   valid;
    string errorMessage;

    bool isValidISBN(string i) const {
        if (i.length() != 5) return false;
        bool hasLetter = false, hasDigit = false;
        for (int k = 0; k < (int)i.length(); k++) {
            if      (isalpha(i[k])) hasLetter = true;
            else if (isdigit(i[k])) hasDigit  = true;
            else return false;
        }
        return hasLetter && hasDigit;
    }

public:
    Book() : title(""), isbn(""), availability(true), dateAdd(""),
             authorCount(0), valid(false), errorMessage("Book data is not initialized.") {}

    Book(string t, string i, bool avail, string d, Author a[], int count) {
        setBookDetails(t, i, avail, d, a, count);
    }

    void setBookDetails(string t, string i, bool avail, string d, Author a[], int count) {
        title = t; isbn = i; availability = avail; dateAdd = d;
        if (count > 2) count = 2;
        authorCount = count;
        for (int k = 0; k < authorCount; k++) authors[k] = a[k];

        valid = true; errorMessage = "";

        if (title == "") {
            valid = false;
            errorMessage = "Error: Title cannot be empty.";
            return;
        }
        if (!isValidISBN(isbn)) {
            valid = false;
            errorMessage = "Error: ISBN must be 5 characters and contain both letters and numbers.";
            return;
        }
    }

    string getTitle()        const { return title; }
    string getISBN()         const { return isbn; }
    bool   getAvailability() const { return availability; }
    string getDateAdd()      const { return dateAdd; }
    int    getAuthorCount()  const { return authorCount; }
    Author getAuthor(int index) const { return authors[index]; }
    bool   isValid()         const { return valid; }
    string getErrorMessage() const { return errorMessage; }

    bool borrowBook() {
        if (!valid || !availability) return false;
        availability = false; return true;
    }
    void returnBook() { availability = true; }

    // Print common fields (no Type line — subclasses handle that)
    void printCommonFields() const {
        if (!valid) cout << getErrorMessage() << endl;
        cout << "Title: " << title << endl;
        cout << "Author: ";
        if (authorCount == 0) {
            cout << "Unknown Author";
        } else {
            for (int k = 0; k < authorCount; k++) {
                cout << authors[k].getFullName();
                if (k < authorCount - 1) cout << ", ";
            }
        }
        cout << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Availability: " << (availability ? "Available" : "Borrowed") << endl;
        cout << "DateAdd: " << dateAdd << endl;
    }

    virtual void displayBookDetails() const {
        printCommonFields();
    }

    virtual ~Book() {}
};

// ============================================================
// HardcopyBook (derived from Book)
// ============================================================
class HardcopyBook : public Book {
private:
    string shelfNumber;
public:
    HardcopyBook() : Book(), shelfNumber("") {}

    void setShelfNumber(string shelf) { shelfNumber = shelf; }
    string getShelfNumber() const { return shelfNumber; }

    void displayBookDetails() const override {
        cout << "Type: Hardcopy" << endl;
        printCommonFields();
        cout << "Shelf Number: " << shelfNumber << endl;
        cout << "-----------------------------" << endl;
    }
};

// ============================================================
// EBook (derived from Book)
// ============================================================
class EBook : public Book {
private:
    string endOfLicenseDate;
public:
    EBook() : Book(), endOfLicenseDate("") {}

    void setEndOfLicenseDate(string date) { endOfLicenseDate = date; }
    string getEndOfLicenseDate() const { return endOfLicenseDate; }

    void displayBookDetails() const override {
        cout << "Type: E-Book" << endl;
        printCommonFields();
        cout << "End of License Date: " << endOfLicenseDate << endl;
        cout << "-----------------------------" << endl;
    }
};

// ============================================================
// Sort — Bubble Sort by ISBN
// ============================================================
void sortBooksByISBN(Book books[], int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (books[j].getISBN() > books[j + 1].getISBN()) {
                Book temp  = books[j];
                books[j]   = books[j + 1];
                books[j+1] = temp;
            }
}

void displayArray(Book books[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "\nBook " << i + 1 << endl;
        books[i].displayBookDetails();
    }
}

// ============================================================
// main
// ============================================================
int main() {

    // ==========================================================
    // Mock Data
    // ==========================================================
    // Correct book authors
    Author hbAuth1[1] = { Author("John",  "Smith")  };
    Author hbAuth2[2] = { Author("Mark",  ""),       Author("Jane", "Taylor") };
    Author ebAuth1[1] = { Author("Anna",  "Lee")    };

    // Incorrect book authors
    Author badAuth1[1] = { Author("John",     "")      };  // title will be empty
    Author badAuth2[1] = { Author("OnlyName", "")       };  // ISBN starts with digit
    Author badAuth3[1] = { Author("",         "Surname") }; // ISBN has special char

    // Sort authors
    Author sortAuth1[1] = { Author("John", "Smith") };
    Author sortAuth2[1] = { Author("Anna", "Lee")   };
    Author sortAuth3[1] = { Author("Mark", "Brown") };

    // ----------------------------------------------------------
    // HardcopyBook — Correct Initialization
    // ----------------------------------------------------------
    cout << "=== Correct HardcopyBook ===" << endl;

    HardcopyBook hb1;
    hb1.setBookDetails("C++ Basics", "A1234", true, "2026-04-21", hbAuth1, 1);
    hb1.setShelfNumber("S1");
    hb1.displayBookDetails();

    HardcopyBook hb2;
    hb2.setBookDetails("Programming Logic", "C3456", true, "2026-04-15", hbAuth2, 2);
    hb2.setShelfNumber("S3");
    hb2.displayBookDetails();

    // ----------------------------------------------------------
    // EBook — Correct Initialization
    // ----------------------------------------------------------
    cout << "=== Correct EBook ===" << endl;

    EBook eb1;
    eb1.setBookDetails("Data Structures", "B2345", false, "2026-04-18", ebAuth1, 1);
    eb1.setEndOfLicenseDate("2027-01-01");
    eb1.displayBookDetails();

    // ----------------------------------------------------------
    // Incorrect Books
    // ----------------------------------------------------------
    cout << "=== Incorrect Books ===" << endl;

    HardcopyBook wrong1;
    wrong1.setBookDetails("", "A1111", true, "2026-04-01", badAuth1, 1);  // empty title
    wrong1.setShelfNumber("X1");
    wrong1.displayBookDetails();
    cout << "[NOTE] Title is empty — title must not be empty." << endl << endl;

    EBook wrong2;
    wrong2.setBookDetails("Network", "12345", false, "2026-04-02", badAuth2, 1);  // ISBN starts with digit
    wrong2.setEndOfLicenseDate("2027-01-01");
    wrong2.displayBookDetails();
    cout << "[NOTE] ISBN '" << wrong2.getISBN() << "' does not start with a letter — must be 1 letter + 4 digits." << endl << endl;

    HardcopyBook wrong3;
    wrong3.setBookDetails("Database", "AB@12", true, "2026-04-03", badAuth3, 1);  // ISBN has special char
    wrong3.setShelfNumber("X3");
    wrong3.displayBookDetails();
    cout << "[NOTE] ISBN '" << wrong3.getISBN() << "' contains invalid character '@'." << endl << endl;

    // ----------------------------------------------------------
    // Sort — 3 arrays in different order, sorted by ISBN
    // ----------------------------------------------------------
    Book ascending[3] = {
        Book("Book A", "A1234", true,  "2026-04-01", sortAuth1, 1),
        Book("Book B", "B2345", true,  "2026-04-02", sortAuth2, 1),
        Book("Book C", "C3456", false, "2026-04-03", sortAuth3, 1)
    };
    Book descending[3] = {
        Book("Book C", "C3456", false, "2026-04-03", sortAuth3, 1),
        Book("Book B", "B2345", true,  "2026-04-02", sortAuth2, 1),
        Book("Book A", "A1234", true,  "2026-04-01", sortAuth1, 1)
    };
    Book mixed[3] = {
        Book("Book B", "B2345", true,  "2026-04-02", sortAuth2, 1),
        Book("Book C", "C3456", false, "2026-04-03", sortAuth3, 1),
        Book("Book A", "A1234", true,  "2026-04-01", sortAuth1, 1)
    };

    cout << "\n=== Ascending order before sort ===" << endl;
    displayArray(ascending, 3);
    sortBooksByISBN(ascending, 3);
    cout << "\n=== Ascending order after sort ===" << endl;
    displayArray(ascending, 3);

    cout << "\n\n=== Descending order before sort ===" << endl;
    displayArray(descending, 3);
    sortBooksByISBN(descending, 3);
    cout << "\n=== Descending order after sort ===" << endl;
    displayArray(descending, 3);

    cout << "\n\n=== Mixed order before sort ===" << endl;
    displayArray(mixed, 3);
    sortBooksByISBN(mixed, 3);
    cout << "\n=== Mixed order after sort ===" << endl;
    displayArray(mixed, 3);

    return 0;
}
