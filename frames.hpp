
#pragma once

#include <ostream>

struct frame_t {
    constexpr frame_t() = default;

    constexpr bool operator==(const frame_t& other) const {
        return this == &other;
    }
};

inline constexpr frame_t ecef_frame{};
inline constexpr frame_t enu_frame{};
inline constexpr frame_t vehicle_frame{};
inline constexpr frame_t launch_rail_frame{};
