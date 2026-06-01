#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

struct NOTE
{
    string family;
    string name;
    string phone;
    int birthDate[3]; // [день, месяц, год]
};

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    const int SIZE = 8;
    NOTE notes[SIZE];
    
    // Ввод данных
    cout << "Введите данные для " << SIZE << " человек:\n";
    for (int i = 0; i < SIZE; i++)
    {
        cout << "\nЧеловек " << (i + 1) << ":\n";
        
        cout << "Фамилия: ";
        cin >> notes[i].family;
        
        cout << "Имя: ";
        cin >> notes[i].name;
        
        cout << "Телефон: ";
        cin >> notes[i].phone;
        
        cout << "Дата рождения (день месяц год через пробел): ";
        cin >> notes[i].birthDate[0] >> notes[i].birthDate[1] >> notes[i].birthDate[2];
    }
    
    // Сортировка по алфавиту (по фамилии + " " + имя)
    sort(notes, notes + SIZE, [](const NOTE &a, const NOTE &b) {
        return a.family + " " + a.name < b.family + " " + b.name;
    });
    
    // Ввод месяца для поиска
    int searchMonth;
    cout << "\nВведите месяц для поиска (1-12): ";
    cin >> searchMonth;
    
    // Поиск и вывод информации
    bool found = false;
    cout << "\nЛюди, родившиеся в месяце " << searchMonth << ":\n";
    
    for (int i = 0; i < SIZE; i++)
    {
        if (notes[i].birthDate[1] == searchMonth)
        {
            cout << "Фамилия: " << notes[i].family << endl;
            cout << "Имя: " << notes[i].name << endl;
            cout << "Телефон: " << notes[i].phone << endl;
            cout << "Дата рождения: " << notes[i].birthDate[0] << "."
                 << notes[i].birthDate[1] << "." << notes[i].birthDate[2] << endl;
            cout << "\n";
            found = true;
        }
    }
    
    if (!found)
        cout << "Люди, родившиеся в этом месяце, не найдены.\n";
    
    return 0;
}
