#pragma once
#include "../dungeon/map.hpp"
#include <Nen/Nen.hpp>
class player_actor : public nen::base_actor {
public:
  player_actor(nen::base_scene &scene);

  void update_move(float delta_time, const map_t &map,
                   const map_actors_t &map_actors);

private:
  nen::vector2 get_input_vector();
};
