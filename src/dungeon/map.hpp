#pragma once
#include <Nen/Nen.hpp>
#include <array>
#include <cstddef>
#include <cstdint>
#include <utility>

constexpr std::pair<std::size_t, std::size_t> map_size = std::make_pair(48, 36);
using map_t = std::array<std::array<uint32_t, map_size.first>, map_size.second>;
using map_actors_t =
    std::array<std::array<std::shared_ptr<nen::base_actor>, map_size.first>,
               map_size.second>;

enum class map_type : uint32_t {
  wall = 0,
  room = 1,
  road = 2,
};