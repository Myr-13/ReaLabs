#include <iostream>

#include <Windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int matrix[4][4] = {
        {1, 2, 3, 4},
        {2, 6, 7, 8},
        {3, 7, 11, 15},
        {4, 14, 15, 16}
    };

    cout << "Матрица:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nЗначения k, где k-я строка совпадает с k-м столбцом:" << endl;
    bool found = false;
    
    for (int k = 0; k < 4; k++) {
        bool matches = true;

        for (int j = 0; j < 4; j++) {
            if (matrix[k][j] != matrix[j][k]) {
                matches = false;
                break;
            }
        }
        
        if (matches) {
            cout << "k = " << (k + 1) << endl;
            found = true;
        }
    }
    
    if (!found)
        cout << "Нет таких k" << endl;
    
    return 0;
}
