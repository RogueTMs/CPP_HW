
#include <iostream>
#include <type_traits>

template <int N, int M = 2>
struct is_prime: std::conditional_t<(N % M == 0), std::integral_constant<bool, false>, is_prime<N, M + 1>> {};

template <int N>
struct is_prime<N, N>: std::integral_constant<bool, true> {};


template <int N>
struct find_next_prime: std::conditional_t<is_prime<N>::value, std::integral_constant<int, N>, find_next_prime<N + 1>> {};


template <int N> 
struct prime: find_next_prime<prime<N - 1>::value + 1> {};

template <> 
struct prime<1>: std::integral_constant<int, 2> {};