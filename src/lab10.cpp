#include <iostream>
#include <string>
#include <locale>
#include <Windows.h>

// Глобальные переменные для задачи 10.1
int g_sum, g_diff, g_prod, g_quot, g_remainder;

// ЗАДАЧА 10.1: Арифметические операции
void ArithmeticOperations()
{
    int num1 = 100, num2 = 25;

    __asm {
        ; Сложение
        mov eax, num1
        add eax, num2
        mov g_sum, eax

        ; Вычитание
        mov eax, num1
        sub eax, num2
        mov g_diff, eax

        ; Умножение
        mov eax, num1
        imul eax, num2
        mov g_prod, eax

        ; Деление
        mov eax, num1
        xor edx, edx          ; очистка старшей части для деления
        mov ecx, num2
        idiv ecx              ; eax = частное, edx = остаток
        mov g_quot, eax
        mov g_remainder, edx
    }
}

// ЗАДАЧА 10.2: Максимум из двух чисел
int MaxOfTwo(int a, int b)
{
    int result;

    __asm {
        mov eax, a            ; eax = a
        cmp eax, b
        jge first_greater
        mov eax, b            ; eax = b (максимум)
        jmp done_max2
    first_greater:
        ; eax уже содержит a
    done_max2:
        mov result, eax
    }

    return result;
}

// Задача 10.3: Максимум из трех чисел
int MaxOfThree(int a, int b, int c)
{
    int result;

    __asm {
        mov eax, a            ; result = a
        cmp eax, b
        jge check_c
        mov eax, b            ; result = b
    check_c:
        cmp eax, c
        jge done_max3
        mov eax, c            ; result = c
    done_max3:
        mov result, eax
    }

    return result;
}

// Задача 10.4: Сумма первых 5 натуральных чисел (JLE)
int Sum5_JLE()
{
    int result;

    __asm {
        xor eax, eax          ; sum = 0
        xor ecx, ecx          ; i = 0
        mov edx, 5            ; max = 5
    loop_jle:
        inc ecx               ; i++
        add eax, ecx          ; sum += i
        cmp ecx, edx
        jle loop_jle
        mov result, eax
    }

    return result;
}

// Задача 10.5: Сумма первых 5 натуральных чисел (JGE)
int Sum5_JGE()
{
    int result;

    __asm {
        xor eax, eax          ; sum = 0
        mov ecx, 5            ; i = 5
    loop_jge:
        add eax, ecx          ; sum += i
        dec ecx               ; i--
        cmp ecx, 0
        jge loop_jge
        mov result, eax
    }

    return result;
}

// Задача 10.6: Сумма первых 5 натуральных чисел (JNE)
int Sum5_JNE()
{
    int result;

    __asm {
        xor eax, eax          ; sum = 0
        xor ecx, ecx          ; i = 0
        mov edx, 5            ; counter = 5
    loop_jne:
        inc ecx               ; i++
        add eax, ecx          ; sum += i
        dec edx               ; counter--
        cmp edx, 0
        jne loop_jne
        mov result, eax
    }

    return result;
}

// Задача 10.7: Сумма первых 5 натуральных чисел (JNZ)
int Sum5_JNZ()
{
    int result;

    __asm {
        xor eax, eax          ; sum = 0
        xor ecx, ecx          ; i = 0
        mov edx, 5            ; counter = 5
    loop_jnz:
        inc ecx               ; i++
        add eax, ecx          ; sum += i
        dec edx               ; counter--
        test edx, edx
        jnz loop_jnz
        mov result, eax
    }

    return result;
}

// Задача 10.8: Сумма первых 5 натуральных чисел (через LOOP)
int Sum5_LOOP()
{
    int result;

    __asm {
        xor eax, eax          ; sum = 0
        xor ecx, ecx          ; i = 0
        mov edx, 5            ; loop counter
    loop_sum:
        inc ecx               ; i++
        add eax, ecx          ; sum += i
        dec edx
        jnz loop_sum
        mov result, eax
    }

    return result;
}

// Задача 10.9: сумма всех (2x) для x=1 до 5
int Sum2x_LOOP()
{
    int result;

    __asm {
        xor eax, eax          ; sum = 0
        xor ecx, ecx          ; x = 0
        mov edx, 5            ; count = 5
    loop_2x:
        inc ecx               ; x++
        mov ebx, ecx
        shl ebx, 1            ; ebx = 2*x (сдвиг = умножение на 2)
        add eax, ebx          ; sum += 2*x
        dec edx
        jnz loop_2x
        mov result, eax
    }

    return result;
}

// Задача 10.10: Факториал
int Factorial(int k)
{
    int result;

    __asm {
        mov eax, 1            ; result = 1
        mov ecx, k            ; counter = k
        cmp ecx, 0
        je factorial_done
    factorial_loop:
        imul eax, ecx         ; result *= counter
        dec ecx               ; counter--
        jnz factorial_loop
    factorial_done:
        mov result, eax
    }

    return result;
}

// Лаба 02, перевел функцию checkNumber на ассемблер
int checkNumber(int num, int m)
{
    int result = 0;

    __asm {
        ; Проверка на четность: if (num % 2 != 0) return 0
        mov eax, num
        test eax, 1
        jnz return_zero_asm

        mov ebx, eax          ; ebx = num (сохраняем оригинал)
        xor edi, edi          ; edi = sum (счётчик суммы цифр)

        ; === Сотни: num / 100 ===
        mov eax, ebx
        xor edx, edx
        mov ecx, 100
        idiv ecx              ; eax = num / 100
        add edi, eax          ; sum += сотни

        ; === Десятки: (num / 10) % 10 ===
        mov eax, ebx
        xor edx, edx
        mov ecx, 10
        idiv ecx              ; eax = num/10, edx = num%10
        mov eax, edx          ; eax = num % 10
        xor edx, edx
        mov ecx, 10
        idiv ecx              ; edx = (num/10) % 10
        add edi, edx          ; sum += десятки

        ; === Единицы: num % 10 ===
        mov eax, ebx
        xor edx, edx
        mov ecx, 10
        idiv ecx              ; edx = num % 10
        add edi, edx          ; sum += единицы

        ; Проверка: if (sum > m) вернуть sum, иначе 0
        cmp edi, m
        jle return_zero_asm

        mov result, edi       ; вернуть сумму
        jmp end_check_asm

    return_zero_asm:
        mov result, 0

    end_check_asm:
        nop
    }

    return result;
}

// Точка входа
int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "=== Задача 10.1: Арифметические операции ===" << std::endl;
    ArithmeticOperations();
    std::cout << "Сумма (100 + 25): " << g_sum << std::endl;
    std::cout << "Разность (100 - 25): " << g_diff << std::endl;
    std::cout << "Произведение (100 * 25): " << g_prod << std::endl;
    std::cout << "Частное (100 / 25): " << g_quot << std::endl;
    std::cout << "Остаток (100 % 25): " << g_remainder << std::endl << std::endl;

    std::cout << "=== Задача 10.2: Максимум из двух чисел ===" << std::endl;
    std::cout << "Max(10, 25) = " << MaxOfTwo(10, 25) << std::endl << std::endl;

    std::cout << "=== Задача 10.3: Максимум из трех чисел ===" << std::endl;
    std::cout << "Max(10, 35, 25) = " << MaxOfThree(10, 35, 25) << std::endl << std::endl;

    std::cout << "=== Задача 10.4: Сумма 5 чисел (JLE) ===" << std::endl;
    std::cout << "Sum = " << Sum5_JLE() << std::endl << std::endl;

    std::cout << "=== Задача 10.5: Сумма 5 чисел (JGE) ===" << std::endl;
    std::cout << "Sum = " << Sum5_JGE() << std::endl << std::endl;

    std::cout << "=== Задача 10.6: Сумма 5 чисел (JNE) ===" << std::endl;
    std::cout << "Sum = " << Sum5_JNE() << std::endl << std::endl;

    std::cout << "=== Задача 10.7: Сумма 5 чисел (JNZ) ===" << std::endl;
    std::cout << "Sum = " << Sum5_JNZ() << std::endl << std::endl;

    std::cout << "=== Задача 10.8: Сумма 5 чисел (через dec/jnz) ===" << std::endl;
    std::cout << "Sum = " << Sum5_LOOP() << std::endl << std::endl;

    std::cout << "=== Задача 10.9: Сумма всех (2x) для x=1..5 ===" << std::endl;
    std::cout << "Sum(2x) = " << Sum2x_LOOP() << std::endl << std::endl;

    std::cout << "=== Задача 10.10: Факториал ===" << std::endl;
    std::cout << "5! = " << Factorial(5) << std::endl;
    std::cout << "7! = " << Factorial(7) << std::endl << std::endl;

    std::cout << "=== Инд. задание ===" << std::endl;
    int m, a, b, c;
    std::cout << "Введите m: ";
    std::cin >> m;
    std::cout << "Введите три числа (a b c): ";
    std::cin >> a >> b >> c;

    std::cout << "\nЧисла, удовлетворяющие условию (Assembly):" << std::endl;
    int sum = checkNumber(a, m);
    if (sum != 0)
        std::cout << a << " (сумма цифр: " << sum << ")" << std::endl;
    sum = checkNumber(b, m);
    if (sum != 0)
        std::cout << b << " (сумма цифр: " << sum << ")" << std::endl;
    sum = checkNumber(c, m);
    if (sum != 0)
        std::cout << c << " (сумма цифр: " << sum << ")" << std::endl;

    return 0;
}
