#include <iostream>

void task1() {
    std::cout << "\n--- Task 1: ввод предложения ---\n";

    // выделяем память под строку (максимум 255 символов + '\0')
    char* buffer = new char[256];

    std::cout << "Введите предложение (до 255 символов):\n";
    std::cin.getline(buffer, 256);

    // 1) считаем количество слов
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

    // 2) находим, какое это слово «по счёту»
    int middle = (wordCount + 1) / 2;  // если слов чётное число, возьмём левое из двух «средних»

    // 3) снова проходим строку, чтобы запомнить границы этого слова
    int current = 0;
    char* start = nullptr;
    char* end = nullptr;
    inWord = false;
    for (char* p = buffer; *p != '\0'; ++p) {
        if (*p != ' ' && !inWord) {
            inWord = true;
            ++current;
            if (current == middle) {
                start = p;  // начало среднего слова
            }
        }
        else if ((*p == ' ' || *(p + 1) == '\0') && inWord) {
            if (current == middle && end == nullptr) {
                // если следующая позиция — '\0', включаем её в конец
                end = (*p == ' ') ? p : p + 1;
                break;
            }
            inWord = false;
        }
    }

    // 4) выводим то, что нашли
    if (start && end) {
        std::cout << "Среднее слово: ";
        for (char* p = start; p != end; ++p) {
            std::cout << *p;
        }
        std::cout << "\n";
    }
    else {
        std::cout << "Не удалось определить среднее слово.\n";
    }

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