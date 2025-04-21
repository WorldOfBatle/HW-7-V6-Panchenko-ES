#include <iostream>

void task1() {
    std::cout << "\n--- Task 1: ввод предложения ---\n";

    // выделяем память под строку (максимум 255 символов + '\0')
    char* buffer = new char[256];

    std::cout << "Введите предложение (до 255 символов):\n";
    std::cin.getline(buffer, 256);

    // подсчитаем количество слов
    int wordCount = 0;
    bool inWord = false;

    for (char* p = buffer; *p != '\0'; ++p) {
        if (*p != ' ' && !inWord) {
            inWord = true;
            ++wordCount;
        }
        else if (*p == ' ' && inWord) {
            inWord = false;
        }
    }

    std::cout << "Количество слов: " << wordCount << "\n";

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