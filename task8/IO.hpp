#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

class IO {
  public:
    virtual bool isOpen() = 0;
    virtual bool isEof() = 0;
    virtual void close() = 0;
    virtual void open() = 0;
};

class Reader : public IO {
  public:
    virtual char readChar() = 0;
    virtual int readInt() = 0;
    virtual std::string readString() = 0;
    virtual std::string readString(const size_t &len) = 0;
};

class Writer : public IO {
  public:
    virtual void write(const char ch) = 0;
    virtual void write(const int &num) = 0;
    virtual void write(const std::string &str) = 0;
};

class ReaderWriter : public Reader, public Writer {
  protected:
    size_t cur_pos = 0;
};

class stringIO : public ReaderWriter {
  protected:
    std::string source;
    bool _open;

  public:
    stringIO() : source({}), _open(true) {
        cur_pos = 0;
    };
    stringIO(const std::string &_source) : source(_source), _open(true) {
        cur_pos = _source.length();
    };
    ~stringIO() { close(); }

    void goToEnd();
    size_t get_cur_pos() const { return cur_pos; }

    bool isOpen() override;
    bool isEof() override;
    void close() override;
    void open() override;

    char readChar() override;
    int readInt() override;
    std::string readString() override;
    std::string readString(const size_t &len) override;

    void write(const char ch) override;
    void write(const int &num) override;
    void write(const std::string &str) override;
};

class fileIO : public ReaderWriter {
  protected:
    FILE *source;
    bool _open;

  public:
    fileIO(const std::string &src_name) : _open(true) {
        source = std::fopen(src_name.c_str(), "r+");
        if (source == NULL) {
            throw new std::runtime_error("Cant open file");
        }
        cur_pos = 0;
    }
    ~fileIO() {
        if (_open)
            close();
    }

    void goToEnd();
    size_t get_cur_pos() const { return cur_pos; }

    bool isOpen() override;
    bool isEof() override;
    void close() override;
    void open() override;

    char readChar() override;
    int readInt() override;
    std::string readString() override;
    std::string readString(const size_t &len) override;

    void write(const char ch) override;
    void write(const int &num) override;
    void write(const std::string &str) override;
};


