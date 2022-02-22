#pragma once
#include <Nen.hpp>
#include <cstddef>

#include "../dungeon/map.hpp"
#include "Utility/dynamic_handler.hpp"
#include "Utility/handle_t.hpp"
#include "player.hpp"

class enemy_actor : public nen::base_actor {
public:
  enemy_actor(nen::base_scene &scene, const player_actor &player,
              const map_t &map, const map_actors_t &map_actors);
  ~enemy_actor() = default;

  void Update(float delta_time) override;
  void move_to_player(float dt, const player_actor &player);

  nen::handle_t rigid_body_handle;
  bool collision(const nen::vector3 &before_pos);

protected:
  const player_actor &player;
  const map_t &map;
  const map_actors_t &map_actors;

private:
};