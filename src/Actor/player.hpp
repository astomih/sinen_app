#pragma once
#include <Nen.hpp>

#include "../dungeon/map.hpp"
#include "Math/Vector2.hpp"
#include "bullet.hpp"
#include <cstdint>
#include <memory>
class player_actor : public nen::base_actor {
public:
  player_actor(nen::base_scene &scene, int x, int y);

  void update_move(float delta_time, const map_t &map,
                   const map_actors_t &map_actors);

  bool collision(const nen::vector3 &before_pos, const map_t &map,
                 const map_actors_t &map_actors);
  void update_bullet(std::vector<uint32_t> &bullets);

  void set_aabb(const nen::aabb &aabb) { m_aabb = aabb; }
  const nen::aabb &get_aabb() const { return m_aabb; }

private:
  nen::aabb m_aabb;
  nen::vector2 get_input_vector();
  nen::vector3 before_before_pos;
};
