#include <iostream>
#include <cassert>
#include "Library.h"

using namespace std;

// ---------------------- Test Functions ----------------------

void testAuthorGetFullName() {
    Author a("Robert", "Martin");
    assert(a.getFullName() == "Robert Martin");
    cout << "[PASS] Author::getFullName()" << endl;
}

void testBookDefaultAvailability() {
    HardcopyBook b;
    b.setBookDetails("Test Book", "0000", true, { Author("John", "Doe") });
    assert(b.isAvailable() == true);
    cout << "[PASS] Book default availability is true" << endl;
}

void testBorrowBook() {
    HardcopyBook b;
    b.setBookDetails("Test Book", "0000", true, { Author("John", "Doe") });
    assert(b.borrowBook() == true);     // first borrow: success
    assert(b.isAvailable() == false);   // now unavailable
    assert(b.borrowBook() == false);    // second borrow: fail
    cout << "[PASS] Book::borrowBook()" << endl;
}

void testReturnBook() {
    HardcopyBook b;
    b.setBookDetails("Test Book", "0000", true, { Author("John", "Doe") });
    b.borrowBook();
    b.returnBook();
    assert(b.isAvailable() == true);
    cout << "[PASS] Book::returnBook()" << endl;
}

void testHardcopyBookShelfNumber() {
    HardcopyBook b;
    b.setBookDetails("Clean Code", "1111", true, { Author("Robert", "Martin") });
    b.setShelfNumber("A1");
    assert(b.getShelfNumber() == "A1");
    cout << "[PASS] HardcopyBook::setShelfNumber() / getShelfNumber()" << endl;
}

void testEBookLicenseDate() {
    EBook e;
    e.setBookDetails("Refactoring", "5555", true, { Author("Martin", "Fowler") });
    e.setEndOfLicenseDate("2026-06-30");
    assert(e.getEndOfLicenseDate() == "2026-06-30");
    cout << "[PASS] EBook::setEndOfLicenseDate() / getEndOfLicenseDate()" << endl;
}

void testLibrarySearchFound() {
    Library lib;
    lib.initializeBooks();
    assert(lib.searchBookByISBN("1111") != -1);
    cout << "[PASS] Library::searchBookByISBN() - found" << endl;
}

void testLibrarySearchNotFound() {
    Library lib;
    lib.initializeBooks();
    assert(lib.searchBookByISBN("9999") == -1);
    cout << "[PASS] Library::searchBookByISBN() - not found" << endl;
}

void testLibraryBorrowAndReturn() {
    Library lib;
    lib.initializeBooks();
    assert(lib.borrowBookByISBN("1111") == true);   // borrow success
    assert(lib.isBookAvailable("1111") == false);   // now unavailable
    assert(lib.borrowBookByISBN("1111") == false);  // borrow again: fail
    assert(lib.returnBookByISBN("1111") == true);   // return success
    assert(lib.isBookAvailable("1111") == true);    // available again
    cout << "[PASS] Library::borrowBookByISBN() / returnBookByISBN()" << endl;
}

void testPolymorphism() {
    Book* b1 = new HardcopyBook();
    Book* b2 = new EBook();
    b1->setBookDetails("Book A", "AAA", true, { Author("A", "B") });
    b2->setBookDetails("Book B", "BBB", true, { Author("C", "D") });
    assert(b1->getISBN() == "AAA");
    assert(b2->getISBN() == "BBB");
    delete b1;
    delete b2;
    cout << "[PASS] Polymorphism: HardcopyBook and EBook as Book*" << endl;
}

// ---------------------- Main ----------------------
int main() {
    cout << "=== Running Test Cases ===" << endl;
    cout << endl;

    testAuthorGetFullName();
    testBookDefaultAvailability();
    testBorrowBook();
    testReturnBook();
    testHardcopyBookShelfNumber();
    testEBookLicenseDate();
    testLibrarySearchFound();
    testLibrarySearchNotFound();
    testLibraryBorrowAndReturn();
    testPolymorphism();

    cout << endl;
    cout << "All tests passed." << endl;

    return 0;
}
