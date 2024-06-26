// --- Day 17: Clumsy Crucible ---

#pragma once

#include <string>

struct Crucible {
    int x, y, dx, dy, speed, heat_loss;

    bool operator==(const Crucible &other) const {
        return x == other.x && y == other.y && dx == other.dx && dy == other.dy && speed == other.speed;
    }

    bool operator>(const Crucible &other) const noexcept { return heat_loss > other.heat_loss; }

    bool operator<(const Crucible &other) const noexcept { return heat_loss < other.heat_loss; }
};

template<>
struct std::hash<Crucible> {
    std::size_t operator()(const Crucible &crucible) const noexcept {
        auto &[x, y, x_dir, y_dir, speed, heat_loss] = crucible;
        return x + y * 1000 + (x_dir + 1) * 1000'000 + (y_dir + 1) * 10'000'000 + speed * 100'000'000;
    }
};
