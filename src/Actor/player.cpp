#include "player.hpp"
#include <Nen.hpp>

player_actor::player_actor(nen::base_scene &scene, int x, int y)
    : nen::base_actor(scene) {}

nen::vector2 player_actor::get_input_vector() {
  nen::vector2 input_vector{};

  if (GetInput().Keyboard.GetKeyState(nen::key_code::LEFT) ==
      nen::button_state::Held) {
    input_vector.x -= 1.0f;
  }
  if (GetInput().Keyboard.GetKeyState(nen::key_code::RIGHT) ==
      nen::button_state::Held) {
    input_vector.x += 1.0f;
  }
  if (GetInput().Keyboard.GetKeyState(nen::key_code::DOWN) ==
      nen::button_state::Held) {
    input_vector.y -= 1.0f;
  }
  if (GetInput().Keyboard.GetKeyState(nen::key_code::UP) ==
      nen::button_state::Held) {
    input_vector.y += 1.0f;
  }

  return input_vector;
}
bool player_actor::collision(const nen::vector3 &before_pos, const map_t &map,
                             const map_actors_t &map_actors) {
  bool is_collied = false;
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 0) {
        int value = nen::collision::IntersectAABB(
            GetPosition(),
            GetScene()
                .get_actor<nen::base_actor>(map_actors[i][j])
                .GetPosition(),
            nen::vector3{GetScale().x * 3.f, GetScale().x * 3.f, 0});
        if (value == 7) {
          SetPosition(before_pos);
          is_collied = true;
        }
      }
    }
  }
  return is_collied;
}

void player_actor::update_move(float delta_time, const map_t &map,
                               const map_actors_t &map_actors) {
  float scale = GetScale().x * 2.f;
  auto input_vector = get_input_vector();
  auto before_pos = GetPosition();

  if (input_vector.x != 0.f && input_vector.y != 0.f) {
    bool x = false, y = false;
    Move(input_vector.x * scale * 2.f * delta_time / nen::Math::Sqrt(2.f), 0,
         0);
    x = collision(before_pos, map, map_actors);
    Move(0, input_vector.y * scale * 2.f * delta_time / nen::Math::Sqrt(2.f),
         0);
    y = collision(GetPosition(), map, map_actors);
    // true x or y
    if (x ^ y) {
      if (x) {
        SetPosition(before_pos);
        Move(0, input_vector.y * scale * 2.f * delta_time, 0);
        collision(GetPosition(), map, map_actors);
      }
      if (y) {
        SetPosition(before_pos);
        Move(input_vector.x * scale * 2.f * delta_time, 0, 0);
        collision(GetPosition(), map, map_actors);
      }
    }
  } else {
    Move(input_vector.x * scale * 2.f * delta_time, 0, 0);
    collision(before_pos, map, map_actors);
    before_pos = GetPosition();
    Move(0, input_vector.y * scale * 2.f * delta_time, 0);
    collision(before_pos, map, map_actors);
  }
  if (input_vector.x != 0 || input_vector.y != 0)
    SetRotation(nen::quaternion::Concatenate(
        nen::quaternion{},
        nen::quaternion{nen::vector3::UnitZ,
                        -nen::Math::Atan2(input_vector.x, input_vector.y)}));
  return;
}