#include "BankAccount.h"

BankAccount::BankAccount() {
    accountNumber = 0;
    name = "";
    adress = "";
}

BankAccount::BankAccount(const BankAccount& bA) {
    this->accountNumber = bA.accountNumber;
    this->name = bA.name;
    this->adress = bA.adress;
}

BankAccount::BankAccount(int accountNumber, string name, string adress) {
    this->accountNumber = accountNumber;
    this->name = name;
    this->adress = adress;
}

int BankAccount::getAccountNumber() const{
    return accountNumber;
}

void BankAccount::setAccountNumber(int accountNumber) {
    this->accountNumber = accountNumber;
}

string BankAccount::getName() const{
    return name;
}

void BankAccount::setName(string name) {
    this->name = name;
}

string BankAccount::getAdress() const{
    return adress;
}

void BankAccount::setAdress(string adress) {
    this->adress = adress;
}

int BankAccount::hashCode(int hashBase) const{
    return accountNumber % hashBase;
}

string BankAccount::toString() const{
    return (string)"BankAccount{" +
           "accountNumber=" + string(7 - to_string(accountNumber).length(), '0') + to_string(accountNumber) + "; " +
           "name=" + name + "; " +
           "adress=" + adress + "}";
}