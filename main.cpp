#include <iostream>

void task1() {
    std::cout << "\n--- Task 1: ввод предложения ---\n";

    // выделяем память под строку (максимум 255 символов + '\0')
    char* buffer = new char[256];

    std::cout << "Введите предложение (до 255 символов):\n";
    // читаем всю строку вместе с пробелами
    std::cin.getline(buffer, 256);

    // пока для проверки просто выводим то, что ввели
    std::cout << "Вы ввели: " << buffer << "\n";

    // не забываем освободить память
    delete[] buffer;
}

void task2() {
    std::cout << "--- Task 2 ---\n";
}

int main() {
    task1();
    task2();
    return 0;
}