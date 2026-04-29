#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
using namespace std;

class Author {
private:
    string firstName;
    string lastName;

public:
    Author();
    Author(string fName, string lName);

    void setAuthorDetails(string fName, string lName);
    string getFirstName() const;
    string getLastName() const;
    string getFullName() const;
};

#endif