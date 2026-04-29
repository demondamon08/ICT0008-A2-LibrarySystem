#include "Author.h"

Author::Author() {
    firstName = "";
    lastName = "";
}

Author::Author(string fName, string lName) {
    setAuthorDetails(fName, lName);
}

void Author::setAuthorDetails(string fName, string lName) {
    firstName = fName;
    lastName = lName;
}

string Author::getFirstName() const {
    return firstName;
}

string Author::getLastName() const {
    return lastName;
}

string Author::getFullName() const {
    if (firstName != "" && lastName != "") {
        return firstName + " " + lastName;
    } else if (firstName != "") {
        return firstName;
    } else if (lastName != "") {
        return lastName;
    } else {
        return "Unknown Author";
    }
}