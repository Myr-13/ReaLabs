#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    // Открываем исходный файл для чтения
    ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        cout << "Ошибка открытия входного файла!" << endl;
        return 1;
    }
    
    // Открываем файлы для записи
    ofstream evenFile("even.txt");   // для четных строк
    ofstream oddFile("odd.txt");     // для нечетных строк
    
    if (!evenFile.is_open() || !oddFile.is_open())
    {
        cout << "Ошибка открытия выходных файлов!" << endl;
        return 1;
    }
    
    string line;
    int lineNumber = 1;
    
    // Читаем файл построчно
    while (getline(inputFile, line))
    {
        if (lineNumber % 2 == 0) // Четная строка
            evenFile << line << endl;
        else // Нечетная строка
            oddFile << line << endl;

        lineNumber++;
    }
    
    // Закрываем файлы
    inputFile.close();
    evenFile.close();
    oddFile.close();
    
    cout << "Файлы успешно созданы!" << endl;
    cout << "Четные строки записаны в файл: even.txt" << endl;
    cout << "Нечетные строки записаны в файл: odd.txt" << endl;
    
    return 0;
}
