#include "player.hpp"

player_actor::player_actor(nen::base_scene &scene) : nen::base_actor(scene) {}

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

void player_actor::update_move(float delta_time, const map_t &map,
                               const map_actors_t &map_actors) {
  auto init_rotate = nen::quaternion{};
  float scale = GetScale().x * 2.f;
  auto input_vector = get_input_vector();
  nen::logger::Debug("%f,%f", input_vector.x, input_vector.y);
  auto before_pos = GetPosition();
  Move(input_vector.x * scale * 2.f * delta_time,
       input_vector.y * scale * 2.f * delta_time, 0);
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 0 && nen::collision::IntersectAABB(
                                GetPosition(), map_actors[i][j]->GetPosition(),
                                nen::vector3(scale * 1.5f, scale, 0))) {
        SetPosition(before_pos);
      }
    }
  }
  if (input_vector.x == 0 && input_vector.y == 0)
    SetRotation(init_rotate);
  else
    SetRotation(nen::quaternion::Concatenate(
        init_rotate,
        nen::quaternion(nen::vector3::UnitZ,
                        -nen::Math::Atan2(input_vector.x, input_vector.y))));
  return;
}