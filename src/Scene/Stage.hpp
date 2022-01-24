#pragma once
#include "../Actor/Camera.hpp"
#include <Nen/Nen.hpp>
#include <array>
#include <cstddef>
#include <cstdint>
#include <utility>

constexpr std::pair<std::size_t, std::size_t> map_size = std::make_pair(48, 36);

enum class map_type : uint32_t {
  wall = 0,
  room = 1,
  road = 2,
};
class Stage : public nen::base_scene {
public:
  Stage();
  void Setup() override;
  void Update(float deltaTime) override;

private:
  std::array<std::array<uint32_t, map_size.first>, map_size.second> map{};
  std::array<std::array<std::shared_ptr<nen::base_actor>, map_size.first>,
             map_size.second>
      map_actors;
  std::shared_ptr<nen::base_actor> player;
  std::unique_ptr<CameraActor> camera;
  std::shared_ptr<nen::texture> white_tex;
};
