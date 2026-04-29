#include <iostream>
#include "Author.h"
#include "Book.h"
#include "Library.h"
#include "Sort.h"
using namespace std;

void displayArray(Book books[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "\nBook " << i + 1 << endl;
        books[i].displayBookDetails();
    }
}

int main() {
    Author a1[1] = { Author("John", "Smith") };
    Author a2[1] = { Author("Anna", "Lee") };
    Author a3[2] = { Author("Mark", ""), Author("Jane", "Taylor") };

    Book correct1("C++ Basics", "A1234", true, "2026-04-21", a1, 1);
    Book correct2("Data Structures", "B2345", false, "2026-04-18", a2, 1);
    Book correct3("Programming Logic", "C3456", true, "2026-04-15", a3, 2);

    Author badAuthors1[1] = { Author("John", "") };
    Author badAuthors2[1] = { Author("OnlyName", "") };
    Author badAuthors3[1] = { Author("", "Surname") };

    Book wrong1("", "A1111", true, "2026-04-01", badAuthors1, 1);          // title empty
    Book wrong2("Network", "12345", false, "2026-04-02", badAuthors2, 1); // no letter
    Book wrong3("Database", "AB@12", true, "2026-04-03", badAuthors3, 1);        // invalid character

    cout << "Correct Book's information" << endl;
    correct1.displayBookDetails();
    cout << endl;
    correct2.displayBookDetails();
    cout << endl;
    correct3.displayBookDetails();

    cout << "\n\nIncorrect Book's information" << endl;
    wrong1.displayBookDetails();
    cout << endl;
    wrong2.displayBookDetails();
    cout << endl;
    wrong3.displayBookDetails();

Book ascending[3] = {
    Book("Book A", "A1234", true, "2026-04-01", a1, 1),
    Book("Book B", "B2345", true, "2026-04-02", a2, 1),
    Book("Book C", "C3456", false, "2026-04-03", a3, 2)
};

Book descending[3] = {
   Book("Book C", "C3456", false, "2026-04-03", a3, 2),
    Book("Book B", "B2345", true, "2026-04-02", a2, 1),
    Book("Book A", "A1234", true, "2026-04-01", a1, 1)

};

Book mixed[3] = {
    Book("Book B", "B2345", true, "2026-04-02", a2, 1),
    Book("Book C", "C3456", false, "2026-04-03", a3, 2),
    Book("Book A", "A1234", true, "2026-04-01", a1, 1)
};
    cout << "\n\nAscending order before sort:" << endl;
    displayArray(ascending, 3);
    sortBooksByISBN(ascending, 3);
    cout << "\nAscending order after sort:" << endl;
    displayArray(ascending, 3);

    cout << "\n\nDescending order before sort:" << endl;
    displayArray(descending, 3);
    sortBooksByISBN(descending, 3);
    cout << "\nDescending order after sort:" << endl;
    displayArray(descending, 3);

    cout << "\n\nMixed order before sort:" << endl;
    displayArray(mixed, 3);
    sortBooksByISBN(mixed, 3);
    cout << "\nMixed order after sort:" << endl;
    displayArray(mixed, 3);

    return 0;
}