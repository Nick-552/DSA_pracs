#include "iostream"
#include "string"
#include "algorithm"
#include "unordered_map"

using namespace std;

void sortStringsInAlphabeticalOrder(string strings[]){
    bool isUnsorted = true;
    while (isUnsorted) {
        isUnsorted = false;
        for (int i = 0; i < strings->size() - 1; i++) {
            if (strings[i] <= strings[i+1])
                continue;
            isUnsorted = true;
            for (; i < strings->size() - 1; i++) {
                if (strings[i] > strings[i + 1])
                    std::swap(strings[i], strings[i + 1]);
            }
        }
    }
}

void printStrings(string strings[]) {
    cout << "Текущий массив {\n";
    for (int i = 0; i < strings->size(); i++) {
        cout << "    " << strings[i] << "\n";
    }
    cout << "}\n";
}

unordered_map<string, int> findAndCount (string strings[], int size, string txt) {
    unordered_map<string, int> hashTable(strings->size());
    for (int i = 0; i < size; i++) {
        const string str = strings[i];
        const int strSize = str.size();

        int lasts[256] = {};
        for(int j = 0; j < 256; j++){
            lasts[j] = strSize;
        }
        for (int j = 0; j < strSize - 1; j++) {
            lasts[(int)str[j]] = strSize - j - 1;
        }

        int counter = 0;
        for (int j = 0; j < txt.size() - str.size() + 1;) {
            bool found = true;
            for (int k = 0; k < strSize; k++){
                if (str[k] != txt[j+k]){
                    found = false;
                    break;
                }
            }
            if (found) {
                counter++;
            }
            j += lasts[txt[j + strSize - 1]];
        }
        hashTable[str] = counter;

    }
    return hashTable;
}

int main(){
    system("chcp 65001");

    cout << "Сортировка массива строк в алфавитном порядке\n";
    string strings[] = {"main", "return", "void", "class", "for", "if"};
    printStrings(strings);
    sortStringsInAlphabeticalOrder(strings);
    printStrings(strings);

    cout << "\nПоиск слов в тексте\n";
    cout<<"Введите число строк которые нужно найти: ";
    int size; cin >> size; cout << "\n";
    string strs[size];
    for (int i = 0; i < size; i++) {
        cout << "Введите " << i + 1 << "-ю строку для поиска: ";
        string s; cin >> s;
        strs[i] = s;
        cout<<"\n";
    }
    cout << "Введите текст в котором нужно искать\n";
    string txt; getline(cin, txt, '\n');
    getline(cin, txt, '\n');

    unordered_map<string, int> hashTable = findAndCount(strs, size, txt);
    cout << "Количество вхождений строк в текст\n";
    for (string str: strs){
        cout << str << ": " << hashTable[str] << ";\n";
    }
    return 0;
}