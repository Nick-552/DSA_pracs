#pragma once
#include "iostream"
#include "string"
using namespace std;

class Note {
    long long INN;
    string surname;
    string telephoneNumber;

public:
    Note();

    Note(long long INN, string sn, string tn);

    long long getINN() const;

    string getSurname() const;

    string getTelephoneNumber() const;

    void setINN(long inn);

    void setSurname(string sn);

    void setTelephoneNumber(string tn);

    string toString() const;

    friend ostream& operator<<(ostream& os, const Note& dt);
};
