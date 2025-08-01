#pragma once
#include <iostream>
template<typename T>
void LogInternal(T&& t) {
    std::cout << t;
}

template<typename T, typename... Args>
void LogInternal(T&& t, Args&&... args) {
    std::cout << t << " ";
    LogInternal(std::forward<Args>(args)...);
}

#define LOG(...) LogInternal(__VA_ARGS__);

