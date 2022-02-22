#pragma once
#include <Nen.hpp>

#include "../Actor/Camera.hpp"
#include "../Actor/player.hpp"
#include "../dungeon/map.hpp"
#include "../model/model.hpp"
#include "Texture/Texture.hpp"
#include <cstdint>
#include <memory>
#include <vector>

class Stage : public nen::base_scene {
public:
  Stage(class nen::manager &_manager);
  void Setup() override;
  void Update(float deltaTime) override;

private:
  void prepare_model();
  void prepare_dungeon();
  void prepare_texture();
  void prepare_actor();
  void prepare_script();
  map_t map{};
  map_actors_t map_actors;
  std::uint32_t handle_camera;
  std::uint32_t handle_player;
  std::uint32_t handle_enemy;
  std::uint32_t m_score;
  std::uint32_t m_handle_font_score;
  std::shared_ptr<nen::texture> white_tex;
  nen::instancing sprite_instancing;
  nen::instancing box_instancing;
  model player_model;
  model spider_model;
  std::shared_ptr<nen::texture> player_texture;
  std::vector<uint32_t> m_bullets;
};
