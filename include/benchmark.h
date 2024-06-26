#pragma once

#include <chrono>
#include <iostream>
#include <string>

namespace benchmark {
    inline std::chrono::time_point<std::chrono::system_clock> start() {
        return std::chrono::high_resolution_clock::now();
    }

    inline void end(const std::chrono::time_point<std::chrono::system_clock> start) {
        const auto end = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        auto output = static_cast<double>(duration.count());

        std::string unit;
        if (output >= 100'000'000) {
            output /= 1'000'000'000;
            unit = "s";
        } else if (output >= 1'000) {
            output /= 1'000'000;
            unit = "ms";
        } else {
            output /= 1'000;
            unit = "us";
        }

        std::cout << "Time: " << output << unit << std::endl;
    }
} // namespace benchmark
