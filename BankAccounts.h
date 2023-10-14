#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "BankAccount.h"

using namespace std;

class BankAccounts
{
    int amountOfElems = 0;
    vector<BankAccount*> accounts;
    int hashBase = 1;
    const int offset = 1;

public:
    BankAccounts();

    BankAccounts(int amount);

    int newHashBase();

    void reFill();

    void addAccount(const BankAccount& bA);

    void addAccounts(vector<BankAccount> bAs);

    BankAccount* findByKey(int key);

    void deleteByKey(int key);

    int findIdxByKey(int key);

    void print();

    int hashCode(int key);
};
