#pragma once

#include <iostream>
#include <string>

using namespace std;

class BankAccount {
    int accountNumber;
    string name;
    string adress;
public:
    BankAccount();

    BankAccount(const BankAccount& bA);

    BankAccount(int accountNumber, string name, string adress);

    int getAccountNumber() const;

    void setAccountNumber(int accountNumber);

    string getName() const;

    void setName(string name);

    string getAdress() const;

    void setAdress(string adress);

    int hashCode(int hashBase) const;

    string toString() const;
};

//#ifndef DSA_PRACS_BANKACCOUNT_H
//#define DSA_PRACS_BANKACCOUNT_H
//
//
//class BankAccount {
//
//};
//
//
//#endif //DSA_PRACS_BANKACCOUNT_H
