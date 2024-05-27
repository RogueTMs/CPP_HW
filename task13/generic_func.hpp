#include <functional>
#include <iostream>

template<typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker&& func, Args&&... args) {  // Luba variant
  size_t index = -1;
  size_t counter = 0;
  
  bool answ = ((func(std::forward<Args>(args)) ? (index = counter, false) : (counter++, true)) && ...);
  return index;
}
