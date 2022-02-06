#pragma once
#include "../dungeon/map.hpp"
#include "player.hpp"
#include <Nen.hpp>

class enemy : public nen::base_actor {
public:
  enemy(nen::base_scene &scene, map_t &map, map_actors_t &map_actors)
      : nen::base_actor(scene), map(map), map_actors(map_actors) {}
  ~enemy() = default;

  void Update(float delta_time) override;

private:
  const map_t &map;
  const map_actors_t &map_actors;
};