#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
using namespace std;

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

#endif
