#include <iostream>

// Вспомогательная функция: проверяет, гласная ли латинская буква
bool isVowel(char c) {
    // приводим к верхнему регистру
    if (c >= 'a' && c <= 'z') c = c - ('a' - 'A');
    // теперь проверяем только верхний регистр
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y';
}

void task1() {
    std::cout << "\n--- Task 1: ввод предложения ---\n";

    // выделяем память под строку (максимум 255 символов + '\0')
    char* buffer = new char[256];

    std::cout << "Введите предложение на английском (до 255 символов):\n";
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

    if (wordCount == 0) {
        delete[] buffer;
        return;
    }

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
                end = (*p == ' ') ? p : p + 1;  // конец среднего слова
                break;
            }
            inWord = false;
        }
    }

    // 4) преобразуем среднее слово в заглавные и выводим всю строку
    if (start && end) {
        for (char* p = start; p < end; ++p) {
            if (*p >= 'a' && *p <= 'z') {
                *p = *p - ('a' - 'A');
            }
        }
        std::cout << "Результат: " << buffer << "\n";
    }
    else {
        std::cout << "Не удалось определить среднее слово.\n";
    }

    delete[] buffer;
}

void task2() {
    std::cout << "\n--- Task 2: удаление символов c1 ---\n";

    // 1) выделяем память под строку
    char* buffer = new char[256];
    std::cout << "Введите строку на английском (до 255 символов):\n";
    std::cin.getline(buffer, 256);

    // 2) читаем символ c1
    std::cout << "Введите символ для удаления (c1): ";
    char c1;
    std::cin >> c1;

    // 3) проходим по строке двумя указателями и «перезаписываем» её без лишних c1
    char* read = buffer;
    char* write = buffer;
    while (*read != '\0') {
        if (*read == c1) {
            // проверяем, окружён ли c1 слева и справа гласными
            bool prevVowel = (read != buffer && isVowel(*(read - 1)));
            bool nextVowel = (*(read + 1) != '\0' && isVowel(*(read + 1)));
            if (!(prevVowel && nextVowel)) {
                // не окружён — пропускаем этот символ
                ++read;
                continue;
            }
        }
        //копируем его
        *write = *read;
        ++write;
        ++read;
    }
    *write = '\0';

    // 4) выводим результат
    std::cout << "Результат: " << buffer << "\n";

    delete[] buffer;
}

int main() {
    task1();
    task2();
    return 0;
}
