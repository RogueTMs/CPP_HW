#include <iostream>
#include <optional>

struct Triple {
    size_t first, second, third;
};

template <typename T> class ScopedPointerDeep {
    T *pointer;

  public:
    ScopedPointerDeep(T *raw) : pointer(raw) {}
    ScopedPointerDeep(const ScopedPointerDeep &other){
        T data = *other.pointer;
        pointer = new T(data);
    }

    ScopedPointerDeep(ScopedPointerDeep &&other){
        pointer = other.pointer;
        other.pointer = nullptr;
    }

    ScopedPointerDeep &operator=(ScopedPointerDeep other) {
        std::swap(pointer, other.pointer);
        return *this;
    }

    std::optional<T> get() {
        if (!pointer)
            return std::nullopt;
        return *pointer;
    }

    const std::optional<T> get() const {
        if (!pointer)
            return std::nullopt;
        return *pointer;
    }

    T &operator*() { return *pointer; }
    const T &operator*() const { return *pointer; }
    T *operator->() { return pointer; }
    const T *operator->() const { return pointer; }

    ~ScopedPointerDeep() { delete pointer; }
};

template <typename T> class ScopedPointerShallow {
    T *pointer;

  public:
    ScopedPointerShallow(T *raw) : pointer(raw) {}
    ScopedPointerShallow(const ScopedPointerShallow &other) = delete;

    ScopedPointerShallow(ScopedPointerShallow &&other)
        : pointer(other.pointer) {
        other.pointer = nullptr;
    }

    ScopedPointerShallow &operator=(ScopedPointerShallow other) {
        if (this != &other) {
            std::swap(pointer, other.pointer);
        }
        return *this;
    }

    std::optional<T> get() {
        if (!pointer)
            return std::nullopt;
        return *pointer;
    }

    const std::optional<T> get() const {
        if (!pointer)
            return std::nullopt;
        return *pointer;
    }

    T &operator*() { return *pointer; }
    const T &operator*() const { return *pointer; }
    T *operator->() { return pointer; }
    const T *operator->() const { return pointer; }

    ~ScopedPointerShallow() { delete pointer; }
};