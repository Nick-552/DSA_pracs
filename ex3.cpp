#include "BankAccounts.h"
#include "BankAccount.h"
#include "random"

char randomGenL() {
    static string charset = "abcdefghijklmnopqrstuvwxyz";
    return charset[rand() % charset.length()];
}


BankAccount generateBankAccount() {
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<int> dist(0, 9999999);

    string adress = "№" + to_string(rand() % 195 + 1);

    int accountNumber = dist(gen);

    int length = rand() % 10 + 12;
    string name(length, ' ');
    for (int i = 0; i < length; i++) {
        if (i == length - 1 || i == length - 3) {
            name[i] = '.';
            continue;
        }
        else if (i == length - 5) {
            continue;
        }
        name[i] = randomGenL();
        if (i == 0 || i == length - 2 || i == length - 4) {
            name[i] += 'A' - 'a';
        }

    }
    BankAccount bA(accountNumber, name, adress);
    //cout << bA.toString() << "\n";
    return bA;
}


int main() {
    system("chcp 65001");
    srand(time(NULL));
    int n;
    cout << "Введите кол-во записей, которые вы хотите добавить в HashTable (1-100):\n";
    while (true) {
        cin >> n;
        if (n < 1 || n > 100) {
            cout << "Введите число из диапазона 1-100: \n";
            continue;
        }
        break;
    }
    BankAccounts hashTable(n);

    while (n--) {
        BankAccount bA = generateBankAccount();
        //cout << bA.toString() << "\n";
        hashTable.addAccount(bA);

    }

    hashTable.print();


    string command = "";
    while (true) {
        cout << "Введите команду (find/add/delete/exit/print): ";
        cin >> command;
        if (command == "exit")
            return 0;
        else if (command == "find") {
            cout << "Введите номер счета: ";
            int key;
            cin >> key;
            BankAccount* result = hashTable.findByKey(key);
            if (result == nullptr) {
                cout << "Номер счета не найден.\n";
            }
            else {
                cout << "Счет найден: " << result->toString() << "\n";
            }
        }
        else if (command == "delete") {
            int key;
            cout << "Введите номер счета: ";
            cin >> key;
            hashTable.deleteByKey(key);
        }
        else if (command == "add") {
            cout << "Введите номер счёта (от 0000000 до 9999999): ";
            int number; cin >> number;
            while (number < 0 || number > 9999999) {
                cout << "Введите номер счёта (от 0000000 до 9999999): ";
                cin >> number;
            }
            cout << "Введите ФИО: ";
            string name;

            getline(cin, name, '\n');
            getline(cin, name, '\n');
            cout << "Введите адрес: ";
            string adress;
            getline(cin, adress, '\n');
            hashTable.addAccount(BankAccount(number, name, adress));
        }
        else if (command == "print") {
            hashTable.print();
        }
        else {
            cout << "Недопустимая команда.\n";
        }
    }
}