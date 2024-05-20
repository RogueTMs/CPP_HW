#include <iostream>
#include <vector>

class MixInException: public std::exception {
    std::string message;

public:
    MixInException(const std::string& message): message(message) { }
    const char* what() const noexcept override { return message.c_str();}
};

template <size_t LIMIT>
class MixIn {
    inline static size_t counter = 0;
public:
    MixIn() {
        if (counter >= LIMIT) throw MixInException("Max number of instances reached!");
        counter++;
    }
    ~MixIn() { counter--;}
};
