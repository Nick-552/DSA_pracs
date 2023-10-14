#include "BankAccounts.h"

BankAccounts::BankAccounts() {
    accounts = { nullptr };
}

BankAccounts::BankAccounts(int amount) {
    hashBase = amount * 4 / 3 + 1;
    accounts = vector<BankAccount*>(amount*4/3 + 1, nullptr);
}

int BankAccounts::newHashBase() {
    if ((double)amountOfElems / hashBase >= 0.75) {
        hashBase *= 2;
        reFill();
    }
    return hashBase;
}

void BankAccounts::reFill() {
    vector<BankAccount*> newAccounts(hashBase, nullptr);
    for (BankAccount* bA : accounts) {
        if (bA == nullptr) continue;
        int idx = bA->hashCode(hashBase);
        while (newAccounts[idx] != nullptr) {
            ++idx %= hashBase;
        }
        newAccounts[idx] = bA;
    }
    accounts = newAccounts;
}


void BankAccounts::addAccount(const BankAccount& bA) {
    BankAccount* bA_ptr = new BankAccount(bA);
    amountOfElems++;
    newHashBase();
    int idx = bA.hashCode(hashBase);
    while (accounts[idx] != nullptr) {
        if (accounts[idx]->getAccountNumber() == bA.getAccountNumber()) {
            amountOfElems--;
            cout << "Банковский аккаунт с таким номером счета уже есть: " << accounts[idx]->toString() << "\n";
            return;
        }
        ++idx %= hashBase;
    }
    accounts[idx] = bA_ptr;
    cout << "Добавлен счет: " << bA_ptr->toString() << "\n";
}

void BankAccounts::addAccounts(vector<BankAccount> bAs) {
    amountOfElems += bAs.size();
    newHashBase();
    amountOfElems -= bAs.size();
    for (auto bA : bAs) {
        addAccount(bA);
    }
}

BankAccount* BankAccounts::findByKey(int key) {
    int idx = findIdxByKey(key);
    if (idx == -1) {
        return nullptr;
    }
    return accounts[idx];
}

void BankAccounts::deleteByKey(int key) {
    int idx = findIdxByKey(key);
    if (idx == -1) {
        cout << "Нет аккаунта с таким номером\n";
        return;
    }
    cout << "Удалён аккаунт: " << accounts[idx]->toString() << "\n";
    delete accounts[idx];
    accounts[idx] = nullptr;

}

int BankAccounts::findIdxByKey(int key) {
    int idx = hashCode(key);
    while (accounts[idx] != nullptr && accounts[idx]->getAccountNumber() != key && ++idx != hashCode(key)) {
        idx %= hashBase;
    }
    if (accounts[idx] == nullptr)
        return -1;
    else
        return idx;
}

void BankAccounts::print() {
    cout << "BankAccounts[hashBase=" << hashBase << ", amountOfElems=" << amountOfElems << "]:\n{\n";
    for (auto bA : accounts) {
        if (bA != nullptr) {
            cout << "  " << bA->toString() << "\n";
        }
//        else
//            cout << "\n";
    }
    cout << "}\n";
}

int BankAccounts::hashCode(int key) {
    return key % hashBase;
}