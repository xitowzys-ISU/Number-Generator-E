/******************************************************************************
     * File: main.cpp
     * Description: Generating the number E
     * Created: 22 Sen 2020
     * Author: Xitowzys
     * Email: xitowzys@gmail.com
 
******************************************************************************/

#include <fstream>
#include <math.h>
#include <thread>
#include <iostream>
#include <malloc/malloc.h>

typedef unsigned long mytype;

// Вкл/Выкл анимации
bool isLoadingAnimation = true;

// Инициализация динамического массива
void setData(mytype* array, const mytype& numberOfArrayElements, const int& highBit = 0);

bool is_zero(const mytype* array, mytype numberOfArrayElements);

void fDiv(mytype *numerator, const int& denominator, const mytype numberSystem, const mytype numberOfArrayElements);

void fAdd(const mytype numberSystem, mytype* x, mytype* y, mytype numberOfArrayElements);

void output(std::ostream& out, const mytype* e, const mytype& size, const mytype numberSystem);

// Анимация выполнения программы
void loadingAnimation();

int main()
{
    using namespace std;

    // Основание система счисления
    mytype numberSystem = 1E10;
    // Количество разрядов exp 1E6
    mytype numberOfDigits = 1E6;
    // Количество элементов массива хранится E
    mytype numberOfArrayElements = (numberOfDigits / log10(numberSystem)) + 1;
    
    // Хранение числа E
    mytype *e = new mytype[numberOfArrayElements];
    // Хранение числа (1 / K!)
    mytype *uk = new mytype[numberOfArrayElements];
    
    // Счетчик для цикла while
    int number = 1;

    // Инициализация массива e
    setData(e, numberOfArrayElements, 1);
    // Инициализация массива e
    setData(uk, numberOfArrayElements, 1);

    // Время начала выполнения программы
    auto startTime = chrono::high_resolution_clock::now();
    
    // Поток для анимации выполнения программы
    thread th(loadingAnimation);
    
    while (!is_zero(uk, numberOfArrayElements)) {
        fDiv(uk, number, numberSystem, numberOfArrayElements);
        fAdd(numberSystem, e, uk, numberOfArrayElements);
        number++;
    }
    
    // Выключить анимацию
    isLoadingAnimation = false;
    
    th.detach();
    
    // Время окончания выполнения программы
    auto endTime = chrono::high_resolution_clock::now();
    
    // Время выполнения программы
    chrono::duration<float> duration = endTime - startTime;
    
    ofstream fout("//Users//xitowzys//Desktop//generated_exp.txt");
    output(fout, e, numberOfArrayElements, numberSystem);
    fout.close();
    
    cout << endl;
    cout << duration.count() << endl;

    return 0;
}

// Инициализация динамического массива
void setData(mytype* array, const mytype& numberOfArrayElements, const int& highBit)
{
    memset(array, 0, sizeof(mytype) * numberOfArrayElements);
    array[0] = highBit;
}

bool is_zero(const mytype* array, mytype numberOfArrayElements)
{
    while (numberOfArrayElements--)
    {
        if (array[numberOfArrayElements])
        {
            return false;
        }
    }
    
    return true;
}

void fAdd(const mytype numberSystem, mytype* x, mytype* y, mytype numberOfArrayElements)
{
    mytype carry = 0;
    
    for (int i = numberOfArrayElements - 1; i >= 0; i--)
    {
        x[i] += y[i] + carry;
        
        if (x[i] >= numberSystem)
        {
            x[i] -= numberSystem;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }
}

void fDiv(mytype *numerator, const int& denominator, const mytype numberSystem, const mytype numberOfArrayElements)
{
    mytype carry = 0, xi, q; //q - Целая часть
    
    for(int i = 0; i < numberOfArrayElements; i++)
    {
        //xi - текущий разряд
        xi = numerator[i] + carry * numberSystem;
        q = mytype(xi / denominator);
        carry = mytype(xi - q * denominator); //carry = xi % d
        numerator[i] = q;
    }
}

// Вывод в файл
void output(std::ostream& out, const mytype* e, const mytype& size, const mytype numberSystem)
{
    using namespace std;
    
    int order = log10(numberSystem);
    
    for (int i = 0; i < size; i++) {
        if (i > 0)
        {
            out << setfill('0') << setw(order);
        }
        
        out << e[i];
        
        if (!i)
        {
            out << '.';
        }
    }
}

// Анимация выполнения программы
void loadingAnimation()
{
    using namespace std;
    
    std::cout << "Выполнение программы";
    while (isLoadingAnimation)
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        std::cout << "." << std::flush;
        this_thread::sleep_for(chrono::milliseconds(500));
        std::cout << "." << std::flush;
        this_thread::sleep_for(chrono::milliseconds(500));
        std::cout << "." << std::flush;
        this_thread::sleep_for(chrono::milliseconds(500));
        std::cout << "\b\b\b   \b\b\b" << std::flush;
    }
}
