#include <functional>
#include <iostream>

template <typename T>
char* allocator(char* ptr, T&& arg) {
  using T_WR = std::remove_reference<T>::type;
  new(ptr) T_WR(arg);
  ptr += sizeof(arg);
  return ptr;
}

template<size_t SIZE, typename... Types>
void allocate(void* memory, Types... args) requires ((SIZE >= (sizeof(Types) + ...)), (std::is_copy_constructible<Types>::value && ...)) {
  char* ptr = (char*) memory;
  ((ptr = allocator(ptr, args)), ...);
}