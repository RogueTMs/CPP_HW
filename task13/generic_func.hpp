#include <functional>
#include <iostream>

template <typename Checker> int get_index(Checker check, int index) {
    return -1;
}

template <typename Checker, typename T, typename... Args>
int get_index(Checker check, int index, T &&first, Args &&...rest) {
    if (check(std::forward<T>(first)))
        return index;
    else
        return get_index(check, index + 1, std::forward<Args>(rest)...);
}

template <typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker checker, Args &&...args) {
    return get_index(checker, 0, std::forward<Args>(args)...);
}