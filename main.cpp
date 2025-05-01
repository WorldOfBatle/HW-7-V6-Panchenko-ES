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

// Читает один символ после вывода подсказки
char readChar(const char* message) {
    std::cout << message;
    char c;
    std::cin >> c;
    std::cin.ignore(1, '\n');  // сбросим '\n' от предыдущего ввода
    return c;
}

// Удаляет из s все символы c1, не окружённые гласными, и возвращает обновлённый буфер
char* removeUnsurrounded(char* s, char c1) {
    char* read = s;
    char* write = s;
    while (*read) {
        if (*read == c1) {
            bool pv = (read != s && isVowel(*(read-1)));
            bool nv = (*(read+1) && isVowel(*(read+1)));
            if (!(pv && nv)) {
                // перевыделяем строку без этого символа
                ptrdiff_t pos = read - s;
                // вычисляем длину строки
                size_t len = 0;
                while (s[len]) {
                    ++len;
                }
                char* t = new char[len]; // len-1 + '\0'
                for (size_t i=0; i<pos; ++i) t[i] = s[i];
                for (size_t i=pos; i<len-1; ++i) t[i] = s[i+1];
                t[len-1] = '\0';
                delete[] s;
                s = t;
                read = s + pos;
                write = s + pos;
                continue;
            }
        }
        *write++ = *read++;
    }
    *write = '\0';
    return s;
}

void task1() {
    std::cout << "\n--- Task 1: ввод предложения ---\n";

    // 1) читаем полное предложение
    char* buffer = readLine("Введите предложение на английском (до 255 символов):\n");

    // 2) считаем количество слов
    int wordCount = countWords(buffer);
    std::cout << "Количество слов: " << wordCount << "\n";

    // если в строке нет слов — сразу выходим
    if (wordCount == 0) {
        delete[] buffer;
        return;
    }

    // 3) находим, какое это слово «по счёту»
    int middle = (wordCount + 1) / 2;

    // 4) находим границы N-го слова
    char *start, *end;
    findWordBounds(buffer, middle, start, end);

    // 5) переводим диапазон в верхний регистр и печатаем
    if (start && end) {
        uppercaseRange(start, end);
        std::cout << "Результат: " << buffer << "\n";
    } else {
        std::cout << "Не удалось определить среднее слово.\n";
    }

    delete[] buffer;
}

void task2() {
    std::cout << "\n--- Task 2: удаление символов c1 ---\n";

    // 1) ввод исходной строки
    char* buffer = readLine("Введите строку на английском (до 255 символов):\n");

    // 2) ввод символа для удаления
    char c1 = readChar("Введите символ для удаления (c1): ");

    // 3) удаляем лишние символы и перезаписываем в тот же буфер
    buffer = removeUnsurrounded(buffer, c1);

    // 4) выводим результат
    std::cout << "Результат: " << buffer << "\n\n";

    // 5) освобождаем память
    delete[] buffer;
}

int main() {
    task1();
    task2();
    return 0;
}