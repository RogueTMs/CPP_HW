#include <iostream>
#include <vector>

template <size_t LIMIT> class MixIn {
    inline static size_t counter = 0;

  public:
    MixIn() {
        if (counter > LIMIT)
            throw std::runtime_error("Too many instances!");
        ++counter;
    }
    MixIn(const MixIn &other) {
        if (counter >  LIMIT)
            throw std::runtime_error("Too many instances!");
        ++counter;
    }
  protected:
    ~MixIn() { --counter; }
};
