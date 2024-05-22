#include "IO.hpp"
#include "bufferedIO.hpp"
#include <charconv>

bool stringIO::isOpen() { return _open; }
bool stringIO::isEof() { return (cur_pos == source.max_size()); }

void stringIO::goToEnd() { cur_pos = source.length(); }

void stringIO::close() {
    if (!_open) {
        std::cerr << "'String' already closed!" << std::endl;
    } else {
        _open = false;
    }
}

void stringIO::open() {
    if (_open) {
        std::cerr << "'String' already opened!" << std::endl;
    } else {
        _open = true;
    }
}

// read
char stringIO::readChar() {
    if (!_open) {
        std::cerr << "'String' closed!" << std::endl;
        return '\0';
    }

    if (cur_pos == 0) {
        std::cerr << "Trying to read from empty string!" << std::endl;
        return '\0';
    }

    cur_pos -= 1;
    return source[cur_pos];
}

int stringIO::readInt() {
    if (!_open) {
        std::cerr << "'String' closed!" << std::endl;
        return 0;
    }

    if (cur_pos == 0) {
        std::cerr << "Trying to read from empty string!" << std::endl;
        return 0;
    }

    std::string ret;
    size_t end_pos = cur_pos;
    char num = this->readChar();
    if (!isdigit(num)) {
        std::cerr << "No int at this position" << std::endl;
        return 0;
    }
    while (isdigit(num)) {
        num = this->readChar();
    }

    return std::stoi(source.substr(cur_pos, end_pos - cur_pos + 1));
}

std::string stringIO::readString() {
    if (!_open) {
        std::cerr << "'String' closed!" << std::endl;
        return "\0";
    }

    cur_pos = 0;
    return source;
}

std::string stringIO::readString(const size_t &len) {
    if (!_open) {
        std::cerr << "'String' closed!" << std::endl;
        return "\0";
    }

    if (cur_pos - len < 0) {
        std::cerr << "Trying to get sting size: " << len
                  << ", but current string have size: " << cur_pos << std::endl;
        return "\0";
    }

    cur_pos = cur_pos - len;
    return source.substr(cur_pos, len);
}

// write
void stringIO::write(const char ch) {
    source.insert(cur_pos, 1, ch);
    cur_pos += 1;
}

void stringIO::write(const int &num) {
    std::string str = std::to_string(num);
    source.insert(cur_pos, str);
    cur_pos += str.length();
}

void stringIO::write(const std::string &str) {
    source.insert(cur_pos, str);
    cur_pos += str.length();
}

bool StringRWBuffered::write_to_resource() {
    int pos = BufferedWriter::index;
    for (size_t i = 0; i < pos; i++) {
        source += BufferedWriter::buffer[i];
    }
    return pos > 0;
}

bool StringRWBuffered::read_from_resource() {
    char ch;
    for (size_t i = 0; i < BufferedReader::buffer_size; i++) {
        ch = read_char();
        BufferedReader::buffer[i] = ch;
    }
    return true;
}
