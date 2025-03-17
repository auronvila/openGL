//
// Created by Auron Vila on 17.03.2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <sstream>

inline void LogHelper(std::ostringstream& stream) {
    std::cout << stream.str() << std::endl;
}

template<typename First, typename... Rest>
void LogHelper(std::ostringstream& stream, First&& first, Rest&&... rest) {
    stream << std::forward<First>(first) << " ";
    LogHelper(stream, std::forward<Rest>(rest)...);
}

template<typename... Args>
void Log(Args&&... args) {
    std::ostringstream stream;
    LogHelper(stream, std::forward<Args>(args)...);
}

#endif
