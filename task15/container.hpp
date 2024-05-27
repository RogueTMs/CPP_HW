#include <functional>
#include <iostream>

template <typename T> char *allocator(char *ptr, T &&arg) {
    using T_WR = std::remove_reference<T>::type;
    new (ptr) T_WR(arg);
    ptr += sizeof(arg);
    return ptr;
}

template <size_t SIZE, typename... Types>
void allocate(void *memory, Types... args) requires(
    (SIZE >= (sizeof(Types) + ...)),
    (std::is_copy_constructible<Types>::value && ...)) {
    char *ptr = (char *)memory;
    ((ptr = allocator(ptr, args)), ...);
}

template <typename... Types> class Container {
  private:
    char mem[(sizeof(Types) + ...)];
    size_t shifts[sizeof...(Types)];
    size_t shift = 0;
    size_t counter = 0;

    template <typename T> void init_shifts(T arg) {
        shifts[counter++] = shift;
        shift += sizeof(T);
    }

  public:
    Container(Types... args) {
        allocate<sizeof(mem)>(mem, args...);
        ((init_shifts<Types>(args)), ...);
    }
    template <typename T> T getElement(size_t idx) {
        return *((T *)(mem + shifts[idx]));
    }
};