#include <random>
#include <fstream>
#include <algorithm>
#include "Note.h"
#include "vector"

struct Pair {
    Pair() {
        INN = -1;
        reference = -1;
    }

    Pair(Note note, int ref) {
        INN = note.getINN();
        reference = ref;
    }
    int reference;
    long long INN; //key
};

bool cmp(Pair p1, Pair p2) {
    return p1.INN < p2.INN;
}

char randomGenLetter() {
    static string charsetLetters = "abcdefghijklmnopqrstuvwxyz";
    return charsetLetters[rand() % charsetLetters.length()];
}

char randomGenDigit() {
    static string charsetDigits = "0123456789";
    return charsetDigits[rand() % charsetDigits.length()];
}

int interpolationSearch(long long inn, vector<Pair> pairs) {
    int l = 0, r = pairs.size() - 1, m;

    while (l < r) {
        m = l + ((long long)r - l) * (min(inn,pairs[r].INN) - pairs[l].INN) / (pairs[r].INN - pairs[l].INN);
        if (pairs[m].INN < inn) {
            l = m + 1;
        }
        else if (pairs[m].INN > inn) {
            r = m - 1;
        }
        else {
            l = r = m;
            break;
        }
    }
    if (l<pairs.size() && pairs[l].INN == inn) {
        return l;
    }
    else {
        return -1;
    }
}

int main() {
    system("chcp 65001");

    // random fill
    srand(time(NULL));
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<unsigned long long> dist(0, 9999999999);

    cout << "Введите количество записей для заполнения файла: ";
    int n; cin >> n;

    int size = sizeof(Note);
    string tn = "+7 (900) 000-00-00";
    Note* note = new Note();
    const string binFilePath = "C:\\Users\\Nick\\Desktop\\for txt files(HW)\\pr2.bin";

    ofstream out(binFilePath, ios::binary | ios::out);
    for (int i = 0; i < n; i++) {
        auto INN = (long long)dist(gen);
        int length = rand() % 7 + 4;
        string name(length, ' ');
        for (int j = 0; j < length; j++) {
            name[j] = randomGenLetter();
            if (j == 0) {
                name[j] += 'A' - 'a';
            }
        }

        for (int j = 0; j < tn.size(); j++) {
            if (j == 5 || j == 6 || j ==  9|| j == 10 || j == 11 || j == 13 || j == 14 || j == 16 || j == 17) {
                tn[j] = rand()%10 + '0';
            }
        }
        note = new Note(INN, name, tn);

        // Выводится один из сгенерированных объектов Note чтобы можно было использовать его для поиска
        if (i == n / 2) {
            cout << *note;
        }

        out.write((char*)note, size); //Записываем объект note в открытый нами файл
    }
    out.close();

    vector<Pair> notes(n);
    fstream in(binFilePath, ios::binary | ios::in);
    for (int i = 0; i < n; i++) {
        in.read((char*)note, size); //Считываем информацию в объект *note
        //cout << *note << "\n";
        notes[i] = Pair(*note, i);
    }

    sort(notes.begin(), notes.end(), cmp);
    cout << "\n";

    cout << "Введите ИНН человека\n";
    long long inn; cin >> inn;


    clock_t start, end;

    // linear search
    cout << "Linear search\n";
    start = clock();
    in.seekg(0);
    for (int i = 0; i < n; i++) {
        in.read((char*)note, size);
        if (note->getINN() == inn) {
            end = clock();
            cout << *note << "\n";
            break;
        }
        else if (i == n - 1) {
            end = clock();
            cout << "Человека с таким ИНН нет\n";
        }
    }
    double seconds = (double)1000*(end - start) / CLOCKS_PER_SEC; // подсчет затраченного времени
    cout << "Времени затрачено: " << seconds << "мс\n";


    // interpolation search
    cout << "Interpolation search\n";
    start = clock();
    int idx = interpolationSearch(inn, notes);
    if (idx > -1) {
        in.seekg(notes[idx].reference * size);
        in.read((char*)note, size);
        end = clock();
        cout << *note << "\n";
    }
    else {
        end = clock();
        cout << "Человека с таким ИНН нет\n";
    }
    seconds = (double)1000*(end - start) / CLOCKS_PER_SEC; // подсчет затраченного времени
    cout << "Времени затрачено: " << seconds << "мс\n";

    in.close();

    system("pause");
    return 0;
}
