#include "Morse.h"
#include <cstring>

struct Pair { char ch; const char* code; };
static const Pair table[] = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
    {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
    {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."},
    {' ', "/"},
    {0, 0}
};

static const char* encodeChar(char c) {
    if (c >= 'a' && c <= 'z') c -= 32;
    for (int i = 0; table[i].ch; i++)
        if (table[i].ch == c) return table[i].code;
    return 0;
}

static char decodeSymbol(const char* code, int len) {
    for (int i = 0; table[i].ch; i++) {
        const char* mc = table[i].code;
        int j = 0;
        while (j < len && mc[j] == code[j]) j++;
        if (j == len && mc[j] == 0) return table[i].ch;
    }
    return '?';
}

Morse::Morse() {
    capacity = 16;
    size = 0;
    data = new char[capacity];
    data[0] = 0;
}

Morse::Morse(const char* encoded) {
    size = strlen(encoded);
    capacity = size + 1;
    data = new char[capacity];
    strcpy(data, encoded);
}

Morse::Morse(const Morse& other) {
    size = other.size;
    capacity = other.capacity;
    data = new char[capacity];
    strcpy(data, other.data);
}

Morse::~Morse() {
    delete[] data;
}

Morse& Morse::operator=(const Morse& other) {
    if (this == &other) return *this;
    delete[] data;
    size = other.size;
    capacity = other.capacity;
    data = new char[capacity];
    strcpy(data, other.data);
    return *this;
}

void Morse::append(const char* str) {
    int len = strlen(str);
    if (size + len + 1 > capacity) {
        capacity = size + len + 1;
        char* nd = new char[capacity];
        strcpy(nd, data);
        delete[] data;
        data = nd;
    }
    strcat(data, str);
    size += len;
}

void Morse::removeFirst(int count) {
    for (int i = 0; i < size - count; i++)
        data[i] = data[i + count];
    size -= count;
    data[size] = 0;
}

Morse Morse::operator+(const Morse& other) {
    Morse r(*this);
    r.append(other.data);
    return r;
}

Morse& Morse::operator+=(const Morse& other) {
    append(other.data);
    return *this;
}

bool Morse::operator==(const Morse& other) {
    return strcmp(data, other.data) == 0;
}

bool Morse::operator!=(const Morse& other) {
    return !(*this == other);
}

Morse& Morse::operator<<(char c) {
    const char* code = encodeChar(c);
    if (!code) return *this;
    if (size > 0) append(" ");
    append(code);
    return *this;
}

Morse& Morse::operator<<(const char* word) {
    for (int i = 0; word[i]; i++)
        (*this) << word[i];
    return *this;
}

Morse& Morse::operator>>(char& c) {
    int i = 0;
    while (i < size && data[i] != ' ') i++;
    c = decodeSymbol(data, i);
    removeFirst(i < size ? i + 1 : i);
    return *this;
}

Morse& Morse::operator>>(char* word) {
    int k = 0;
    while (size > 0) {
        if (data[0] == '/') {
            removeFirst(size > 1 ? 2 : 1);
            break;
        }
        int i = 0;
        while (i < size && data[i] != ' ') i++;
        word[k++] = decodeSymbol(data, i);
        removeFirst(i < size ? i + 1 : i);
    }
    word[k] = 0;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Morse& m) {
    out << m.data;
    return out;
}

std::istream& operator>>(std::istream& in, Morse& m) {
    char buf[1024];
    in.getline(buf, 1024);
    m = Morse(buf);
    return in;
}
