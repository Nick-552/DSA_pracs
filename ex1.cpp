#include <iostream>
#include <bitset>
#include <cstdlib>
#include <Windows.h>
#include <cmath>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

unsigned long long input(unsigned long long maxx, string msg) { // Ввод целого числа из диапазона [0, maxx) с пояснением для ввода msg
    unsigned long long x;
    cout << "Введите целое число " << msg << " в диапазоне[0, " << maxx << "): ";
    cin >> x;
    while (x < 0 || x >= maxx) {
        cout << "Неверный ввод. Введите целое число " << msg << " в диапазоне[0, " << maxx << "): ";
        cin >> x;
    }
    return x;
}

unsigned char task1a() { //установка 5 бита числа в 0
    unsigned char x = input(1 << 8, "x");
    unsigned char maska = 1;	//1=00000001 – 8-разрядная маска
    x = x & (~(maska << 4));
    cout << "x = " << (short)x << endl;
    return x;
}

unsigned char task1b() { //установка 7 бита числа в 1
    unsigned char x = input(1 << 8, "x");
    unsigned char maska = 1;	//1=00000001 – 8-разрядная маска
    x = x | (maska << 6); //maska << 6  -  число у которого 1 только в 7 бите
    cout << "x = " << (short)x << endl;
    return x;
}

void task1v() {   // Получение и вывод двоичной записи десятичного числа

    const int n = sizeof(int) * 8; // = 32 - кол-во битов в числе типа int
    unsigned int x = input((unsigned long long)1 << n, "x");
    unsigned maska = (1 << n - 1); // 1 в старшем бите разрядной сетки
    cout << "Начальный вид маски: " << bitset<n>(maska) << endl;
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) { // 32 раза - по количеству разрядов
        cout << ((x & maska) >> (n - i)); //Выводится (n-i)-ый бит числа x & maska, (n-i) бит в числе maska - единственный бит равный 1
        maska = maska >> 1; // смещение на 1 бит в маске вправо
    }
    cout << endl;
}

void task1() { //Выбор пункта задания и его выполнение
    cout << "Выберите пункт задания (а, б или в): ";
    char c; cin >> c;
    switch (c)
    {
        case 'а': {
            cout << "Установка 5-го бита числа в 0: \n";
            task1a(); //Выполнение пункта 1а
            break;
        }
        case 'б': {
            cout << "Установка 7-го бита числа в 1: \n";
            task1b(); //Выполнение пункта 1б
            break;
        }
        case 'в': {
            cout << "Преобразование десятичного числа в двоичное: \n";
            task1v(); //Выполнение пункта 1в
            break;
        }
        default: {
            cout << "Такого пункта нет\n";
        }
    }
    system("pause");
}



void task2a() {
    unsigned short k = input(9, "(количество чисел в массиве)");

    unsigned char m = 0; //используется как битовый массив
    cout << "Введите " << k << " чисел в диапазоне [0, " << 8 << ")\n";
    while (k--) {
        int i = input(8, "");
        m = m | (1 << i); //установка 1 в бит с номером i
    }

    cout << "Отсортированный массив: {";
    for (int i = 0; i < 8; i++) { //вывод номеров битов в порядке возрастания, при условии, что они равны единице
        if ((1 << i) & m) {
            cout << " " << i;
        }
    }
    cout << "}\n";
}

void task2b() {
    unsigned short k = input(65, "(количество чисел в массиве)");
    unsigned long long m = 0; //используется как битовый массив
    cout << "Введите " << k << " чисел в диапазоне [0, " << 64 << ")\n";
    while (k--) {
        int i = input(64, ""); //ввод числа исходного массива
        m = m | ((unsigned long long)1 << i); //установка 1 в бит с номером i
    }
    cout << "Отсортированный массив: {";
    for (int i = 0; i < 64; i++) { //вывод номеров битов в порядке возрастания, при условии, что они равны единице
        if (((unsigned long long)1 << i) & m) {
            cout << " " << i;
        }
    }
    cout << "}\n";
}

void task2v() {

    unsigned short k = input(65, "(количество чисел в массиве)");

    int n = 0;
    while (n < k)n += 8;
    int m_size = max(1, n / 8); //определение нужного размера для массива чисел, который будет использован как битовый массив
    cout << n;


    unsigned char* m = new unsigned char[m_size]; //используется как битовый массив
    for (int i = 0; i < m_size; i++) {
        m[i] = 0;
    }
    cout << "Введите " << k << " чисел в диапазоне [0, " << n << ")\n";
    while (k--) { //ввод чисел исходного масссива и установка 1 в соответствующий бит битового масссива
        int a = input(n, "");
        m[a / 8] = m[a / 8] | (1 << a % 8); // a/8 - номер числа в битовом массиве, бит которого нужно изменить
    }
    cout << "Отсортированный массив: {";
    for (int i = 0; i < n; i++) {
        if (((unsigned long long)1 << i % 8) & m[i / 8]) {
            cout << " " << i;
        }
    }
    cout << "}\n";
}



void task2() { // выбор пункта задания 2 и выполнение соответствующей процедуры
    cout << "Выберите пункт задания (а, б или в): ";
    unsigned char c; cin >> c;
    switch (c)
    {
        case 'а': {
            task2a();
            break;
        }
        case 'б': {
            task2b();
            break;
        }
        case 'в': {
            task2v();
            break;
        }
        default: {
            cout << "Такого пункта нет\n";
        }
    }
    system("pause");
}

void task3() {
    const int arr_size = 10000000;


    clock_t start = clock();
    ofstream fout("C:\\Users\\Nick\\Desktop\\for txt files(HW)\\txtfile.txt");
    for (int i = 9999999; i >= 10; i--) {

        fout << i << " ";
    }
    fout.close();
    clock_t end = clock();

    cout << "filled\n";
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Времени затрачено: " << seconds << "с\n";

    start = clock();
    bool* arr = new bool[arr_size];
    for (int i = 0; i < arr_size; i++) {
        arr[i] = 0;
    }
    end = clock();
    cout << "set0\n";
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Времени затрачено: " << seconds << "с\n";

    start = clock();
    ifstream fin("C:\\Users\\Nick\\Desktop\\for txt files(HW)\\txtfile.txt");
    int a = 0;
    while (!fin.eof()) { // Чтение исходного массив происходит из файла
        fin >> a;
        arr[a] = 1;
    }
    fin.close();
    end = clock();
    cout << "bitset filled\n";
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Времени затрачено: " << seconds << "с\n";

    start = clock();
    fout.open("C:\\Users\\Nick\\Desktop\\for txt files(HW)\\txtfile.txt");

    for (int i = 0; i < arr_size; i++) { // заполнение файла в отсортированном виде
        if (arr[i]) {
            fout << i << ' ';
        }
        if (i % 100 == 0) {
            fout << '\n';
        }
    }
    fout.close();
    end = clock();
    cout << "file filled with sorted\n";
    seconds = (double)(end - start) / CLOCKS_PER_SEC; // подсчет затраченного времени
    cout << "Времени затрачено: " << seconds << "с\n";
    cout << "Памяти затрачено: " << sizeof(bool) * arr_size / (1024. * 1024 * 8) << "МБ" << "\n";
}

int main() {
    system("chcp 65001");

    int task_number;
    bool doing_tasks = true;
    while (doing_tasks) {
        cout << "Выберите номер задания (1, 2 или 3) или 0, если хотите завершить программу: ";
        cin >> task_number;
        switch (task_number)
        {
            case 0: {
                doing_tasks = false;
                break;
            }
            case 1: {
                task1();
                break;
            }
            case 2: {
                task2();
                break;
            }
            case 3: {
                task3();
                break;
            }
            default:
                cout << "Некорректный номер задания\n";
        }
    }
    int n = 5;
    cout << "Взрыв через ";
    while (n)
    {
        cout << n-- << "..";
        chrono::seconds dura(1);
        this_thread::sleep_for(dura);
        cout << "\b\b\b";

    }
    system("cls");
    cout << "BOOOOOOOOOOOOOM!";
    return 0;
}