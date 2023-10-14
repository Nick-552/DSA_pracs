#include "Note.h"

Note::Note() {
    INN = 0;
    surname = "Surname";
    telephoneNumber = "+7 (900) 000-00-00";
}

Note::Note(long long INN, string sn, string tn) {
    this->INN = INN;
    this->surname = sn;
    this->telephoneNumber = tn;
}

long long Note::getINN() const {
    return INN;
}

string Note::getSurname() const {
    return surname;
}

string Note::getTelephoneNumber() const {
    return telephoneNumber;
}

void Note::setINN(long inn) {
    INN = inn;
}

void Note::setSurname(string sn) {
    surname = sn;
}

void Note::setTelephoneNumber(string tn) {
    telephoneNumber = tn;
}

string Note::toString() const {
    string inn = to_string(INN);
    inn = string(10 - inn.length(), '0') + inn;
    string s = "Note {INN = " + inn + ", surname = " + surname + ", telephoneNumber = " + telephoneNumber + " }";
    return s;
}

ostream& operator<<(ostream& os, const Note& note) {
    os << note.toString();
    return os;
}