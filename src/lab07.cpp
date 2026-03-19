#include <iostream>
#include <string>
#include <sstream> // Подключаем библиотеку для работы с потоками строк
#include <Windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    string s;
    cout << "Введите строку S: ";
    // Использую getline, а не cin, т.к. нужно читать полностью строку, а sin читает только до первого пробела
    getline(cin, s);

    istringstream stream(s);

    int number;
    int min_val, max_val;

    if (stream >> number) {
        min_val = number;
        max_val = number;

        while (stream >> number) {
            if (number > max_val) {
                max_val = number;
            }
            if (number < min_val) {
                min_val = number;
            }
        }

        cout << "Максимальное число: " << max_val << endl;
        cout << "Минимальное число: " << min_val << endl;
    }

    return 0;
}
