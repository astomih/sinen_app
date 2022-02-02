#pragma once
#include "../Actor/Camera.hpp"
#include "../Actor/player.hpp"
#include "../dungeon/map.hpp"

class Stage : public nen::base_scene {
public:
  Stage();
  void Setup() override;
  void Update(float deltaTime) override;

private:
  map_t map{};
  map_actors_t map_actors;
  std::uint16_t camera_handle;
  std::unique_ptr<player_actor> m_player;
  std::shared_ptr<nen::texture> white_tex;
};
