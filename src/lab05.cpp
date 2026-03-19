#include <iostream>
#include <cstdlib>
#include <algorithm>

#include <Windows.h>

using namespace std;

void print_array(int *arr, int n)
{
    if (n == 0)
    {
        cout << "Массив пуст." << endl;
        return;
    }

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;
}

int menu()
{
    cout << "\nВыберите пункт:" << endl;
    cout << "1 - Удалить элементы (N элементов, начиная с номера K)" << endl;
    cout << "2 - Добавить элементы (K элементов в начало массива)" << endl;
    cout << "3 - Выполнить перестановку (Поменять местами мин. и макс. элементы)" << endl;
    cout << "4 - Поиск элементов (Первый четный)" << endl;
    cout << "5 - Выполнить сортировку элементов (Сортировка пузырьком)" << endl;
    cout << "0 - Выход" << endl;

    int choice;
    cin >> choice;
    return choice;
}

void delete_elements(int **arr, int *n, int start_index, int count)
{
    int new_n = *n - count;
    int *new_arr = new int[new_n];

    for (int i = 0; i < start_index; i++)
        new_arr[i] = (*arr)[i];

    for (int i = start_index + count; i < *n; i++)
        new_arr[i - count] = (*arr)[i];

    delete[] arr;
    *arr = new_arr;
    *n = new_n;

    cout << "Элементы удалены." << endl;
}

void add_elements(int **arr, int *n, int count)
{
    int new_n = *n + count;
    int *new_arr = new int[new_n];

    for (int i = 0; i < count; i++)
        new_arr[i] = rand() % 1000;

    for (int i = 0; i < *n; i++)
        new_arr[i + count] = (*arr)[i];

    delete[] arr;
    *arr = new_arr;
    *n = new_n;

    cout << "Элементы добавлены." << endl;
}

void swap_min_max(int *arr, int n)
{
    if (n == 0) return;

    int min_idx = 0, max_idx = 0;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[min_idx]) min_idx = i;
        if (arr[i] > arr[max_idx]) max_idx = i;
    }

    swap(arr[min_idx], arr[max_idx]);
    cout << "Элементы поменять местами." << endl;
}

void find_first_even(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 == 0)
        {
            cout << "Первый четный элемент: " << arr[i] << " (Индекс: " << i << ")" << endl;
            return;
        }
    }

    cout << "Четных элементов не найдено." << endl;
}

void bubble_sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
    cout << "Массив отсортирован." << endl;
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n = 0, choice = 0;
    bool running = true;

    cout << "Введите размер массива: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Размер должен быть положительным." << endl;
        return 1;
    }

    int *arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;

    cout << "Исходный массив:" << endl;
    print_array(arr, n);

    while (running)
    {
        choice = menu();

        switch (choice)
        {
        case 1:
        {
            int k, count;
            cout << "Введите K: ";
            cin >> k;
            cout << "Введите N: ";
            cin >> count;
            delete_elements(&arr, &n, k, count);
            print_array(arr, n);
            break;
        }
        case 2:
        {
            int k;
            cout << "Введите K: ";
            cin >> k;
            add_elements(&arr, &n, k);
            print_array(arr, n);
            break;
        }
        case 3:
            swap_min_max(arr, n);
            print_array(arr, n);
            break;
        case 4:
            find_first_even(arr, n);
            break;
        case 5:
            bubble_sort(arr, n);
            print_array(arr, n);
            break;

        case 0:
        default:
            running = false;
            break;
        }
    }

    delete[] arr;

    return 0;
}
