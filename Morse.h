#pragma once
#include <iostream>

class Morse {
public:
    char* data;
    int size;
    int capacity;
    Morse();
    Morse(const char* encoded);
    Morse(const Morse& other);
    ~Morse();
    Morse& operator=(const Morse& other);
    Morse operator+(const Morse& other);
    Morse& operator+=(const Morse& other);
    bool operator==(const Morse& other);
    bool operator!=(const Morse& other);
    Morse& operator<<(char c);
    Morse& operator<<(const char* word);
    Morse& operator>>(char& c);
    Morse& operator>>(char* word);
    void append(const char* str);
    void removeFirst(int count);
};

std::ostream& operator<<(std::ostream& out, const Morse& m);
std::istream& operator>>(std::istream& in, Morse& m);
