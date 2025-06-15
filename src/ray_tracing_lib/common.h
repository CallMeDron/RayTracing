#pragma once

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T, typename... Args>
void print(const T& first, const Args&... args) {
    std::cout << first;
    if constexpr (sizeof...(args) > 0) {
        std::cout << " ";
        print(args...);
    } else {
        std::cout << std::endl;
    }
}