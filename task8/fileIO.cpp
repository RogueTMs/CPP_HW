#include "IO.hpp"
#include <charconv>

bool fileIO::isOpen() { return _open; }
bool fileIO::isEof() { return std::feof(source); }

// void stringIO::goToEnd(){
//     cur_pos = source.length();
// }

void fileIO::close() {
    if (!_open) {
        std::cerr << "File already closed!" << std::endl;
    } else {
        _open = false;
        std::fclose(source);
        source = NULL;
    }
}

void fileIO::open() {
    if (!_open) {
        std::cerr << "File already closed!" << std::endl;
    }
}

// read
char fileIO::readChar() {
    std::cout << cur_pos << std::endl;

    if (!_open) {
        std::cerr << "File closed!" << std::endl;
        return '\0';
    }

    if (cur_pos == 0) {
        std::cerr << "Trying to read from empty file!" << std::endl;
        return '\0';
    }
    
    char ch;
    std::fseek(source, --cur_pos, SEEK_SET);
    std::fscanf(source, "%c", &ch);
    return ch;
    // }
}

int fileIO::readInt() {
    if (!_open) {
        std::cerr << "File closed!" << std::endl;
        return 0;
    }

    if (cur_pos == 0) {
        std::cerr << "Trying to read from empty file!" << std::endl;
        return 0;
    }

    
    size_t end_pos = cur_pos;
    char num = this->readChar();
    if (!isdigit(num)) {
        std::cerr << "No int at this position" << std::endl;
        return 0;
    }
    while (isdigit(num)) {
        num = this->readChar();
    }

    char* ret;
    std::fscanf(source, "%s", ret);

    std::fseek(source, end_pos - cur_pos + 1, cur_pos);
    return std::stoi(std::string(ret));
}

std::string fileIO::readString() {
    if (!_open) {
        std::cerr << "File closed!" << std::endl;
        return "\0";
    }

    std::string ret;
    while (cur_pos != 0){
        ret.push_back(this->readChar());
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}
std::string fileIO::readString(const size_t &len) {
    if (!_open) {
        std::cerr << "'String' closed!" << std::endl;
        return "\0";
    }

    if (cur_pos - len < 0) {
        std::cerr << "Trying to get sting size: " << len
                  << ", but current string have size: " << cur_pos << std::endl;
        return "\0";
    }
    std::string ret;
    for (size_t _ = 0; _ < len; _++){
        ret.push_back(this->readChar());
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

// write
void fileIO::write(const char ch) {
    fseek(source, cur_pos, 0);
    fprintf(source, "%c", ch);
    cur_pos += 1;
}

void fileIO::write(const int &num) {
    std::string str = std::to_string(num);
    this->write(str);
}

void fileIO::write(const std::string &str) {
    const int length = str.length(); 
    char* char_array = new char[length + 1]; 
    strcpy(char_array, str.c_str());
    for(int i = 0; i < length; i++){
        this->write(char_array[i]);
    }

    delete[] char_array;
}