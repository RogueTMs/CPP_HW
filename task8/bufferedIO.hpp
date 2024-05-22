#pragma once

#include "IO.hpp"

class Buffered {
  protected:
    size_t index = 0;
    size_t buffer_size;
    char* buffer;

    void roll_back() { index = 0; }

  public:
    Buffered(size_t buffer_size_): buffer_size(buffer_size_) {
      buffer = new char[buffer_size];
    }
    ~Buffered() { delete[] buffer; }
};

class BufferedReader : public Buffered, public Reader {
  protected:
    virtual bool read_from_resource() = 0;

    char get() {
        if (index == 0 || index == buffer_size) { // empty buffer
            bool status = read_from_resource();
            roll_back();
        }
        return buffer[index++];
    }

  public:
    BufferedReader(size_t buffer_size_) : Buffered(buffer_size_) {}
    char read_char() { return get(); }

    int read_int() {
        std::string num;
        char ch = get();
        while (ch != ' ') {
            if (!isdigit(ch)) {
                std::cerr << "No int at this position" << std::endl;
                return 0;
            }
            num += ch;
            ch = get();
        }
        return stoi(num);
    }

    std::string read_string() {
        std::string str;
        char ch = get();
        while (ch != ' ') {
            str += ch;
            ch = get();
        }
        return str;
    }
};

class BufferedWriter : public Buffered, public Writer {
  protected:
    virtual bool write_to_resource() = 0;

    void append(const char &ch) {
        if (index == buffer_size) {
            write_to_resource();
            roll_back();
        }
        buffer[index++] = ch;
    }

  public:
    BufferedWriter(size_t buffer_size_) : Buffered(buffer_size_) {}
    void write(const char &ch) { append(ch); }

    void write(const int &num) {
        std::string str = std::to_string(num);
        for (const char &ch : str) {
            append(ch);
        }
    }

    void write(const std::string &str) {
        for (const char &ch : str) {
            append(ch);
        }
    }
};

class BufferedRW : public BufferedReader, public BufferedWriter {
  public:
    BufferedRW(size_t buffer_size)
        : BufferedWriter(buffer_size), BufferedReader(buffer_size) {}
};

class StringRWBuffered : public stringIO, public BufferedRW {
  public:
    StringRWBuffered(int buffer_size) : BufferedRW(buffer_size) {}
    StringRWBuffered() : BufferedRW(100) {}

    bool write_to_resource();

    bool read_from_resource();
};