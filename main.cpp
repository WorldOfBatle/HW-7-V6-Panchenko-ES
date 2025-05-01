#include <iostream>
#include <cstddef>      // для size_t и ptrdiff_t

// Читает строку (до 255 символов) в динамический буфер
char* readLine(const char* message) {
    std::cout << message;
    char* buf = new char[256];
    std::cin.getline(buf, 256);
    return buf;
}

// Считает количество слов в строке (разделитель — пробел)
int countWords(const char* s) {
    bool inWord = false;
    int cnt = 0;
    for (const char* p = s; *p; ++p) {
        if (*p != ' ' && !inWord) {
            inWord = true;
            ++cnt;
        }
        else if (*p == ' ' && inWord) {
            inWord = false;
        }
    }
    return cnt;
}

// Находит в строке s N-е слово, возвращает через start/end (не включая end)
void findWordBounds(char* s, int N, char*& start, char*& end) {
    bool inWord = false;
    int cur = 0;
    start = end = nullptr;
    for (char* p = s; *p; ++p) {
        if (*p != ' ' && !inWord) {
            inWord = true;
            ++cur;
            if (cur == N) start = p;
        }
        else if ((*p == ' ' || *(p+1) == '\0') && inWord) {
            if (cur == N && !end) {
                end = (*p == ' ') ? p : p+1;
                return;
            }
            inWord = false;
        }
    }
}

// Переводит все буквы в диапазоне [start,end) в верхний регистр
void uppercaseRange(char* start, char* end) {
    for (char* p = start; p < end; ++p) {
        if (*p >= 'a' && *p <= 'z') {
            *p = *p - ('a' - 'A');
        }
    }
}

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
    char* read  = buffer;
    char* write = buffer;
    while (*read != '\0') {
        if (*read == c1) {
            // проверяем, окружён ли c1 слева и справа гласными
            bool prevVowel = (read != buffer &&       isVowel(*(read - 1)));
            bool nextVowel = (*(read + 1) != '\0' && isVowel(*(read + 1)));
            if (!(prevVowel && nextVowel)) {
                // нашли «лишний» c1 — перевыделяем буфер без него
                ptrdiff_t pos = read - buffer;           // индекс текущей позиции
                // узнаём старую длину
                size_t oldLen = 0;
                while (buffer[oldLen] != '\0') ++oldLen;
                size_t newLen = oldLen - 1;              // новая длина без одного символа

                // создаём временный буфер
                char* tmp = new char[newLen + 1];        // +1 для '\0'
                // копируем всё до pos
                for (size_t k = 0; k < (size_t)pos; ++k)
                tmp[k] = buffer[k];
                // копируем остаток после pos
                for (size_t k = pos; k < newLen; ++k)
                tmp[k] = buffer[k + 1];
                tmp[newLen] = '\0';

                // после перевыделения буфера:
                delete[] buffer;
                buffer = tmp;

                // возвращаемся на ту же позицию в обновлённом буфере
                read  = buffer + pos;
                write = buffer + pos;
                continue;
            }
        }
        // копируем прочие символы
        *write = *read;
        ++write;
        ++read;
    }
    *write = '\0';

    // выводим результат
    std::cout << "Результат: " << buffer << "\n";

    // удаляем единожды выделенный буфер
    delete[] buffer;
}

int main() {
    task1();
    task2();
    return 0;
}
