#include "enemy.hpp"
enemy_actor::enemy_actor(nen::base_scene &scene, const player_actor &player,
                         const map_t &map, const map_actors_t &map_actors)
    : nen::base_actor(scene), player(player), map(map), map_actors(map_actors) {

  /*
auto &lua = GetScene().get_script().get_sol_state();
lua["enemy_collision"] = &enemy_actor::collision;
lua.new_usertype<enemy_actor>("enemy_t", "collision",
                            &enemy_actor::collision);
                            */
}

void enemy_actor::Update(float delta_time) {
  float z = nen::Math::Sin0_1(2) * 2;
  if (z < 0.f)
    z = 0.f;
  SetPosition(nen::vector3(GetPosition().x, GetPosition().y, z));
}

void enemy_actor::move_to_player(float dt, const player_actor &player) {
  /*
  auto &lua = GetScene().get_script().get_sol_state();
  get_component<nen::rigidbody_component>(rigid_body_handle).Update(dt);
  lua.require_file("utility", nen::asset_reader::ConvertFilePath(
                                  "utility.lua", nen::asset_type::Script));
  lua.script_file(
      nen::asset_reader::ConvertFilePath("enemy.lua", nen::asset_type::Script));
  lua["delta_time"] = dt;
  lua["move_to_player"]();
  lua["enemy_body"] = this;
  */
  /*
  auto player_pos = player.GetPosition();
  auto before = GetPosition();
  auto dir = player_pos - before;
  dir.Normalize();
  dir *= 10.f * dt;
  nen::quaternion q(nen::vector3::UnitZ, -nen::Math::Atan2(dir.x, dir.y));
  SetRotation(q);
  Move(dir);
  if (collision(before)) {
    Move(dir.x, 0, 0);
    if (!collision(before))
      return;
    Move(0, dir.y, 0);
    collision(before);
  }
  */
}

bool enemy_actor::collision(const nen::vector3 &before_pos) {
  bool is_collied = false;
  nen::aabb enemy_aabb =
      get_component<nen::rigidbody_component>(rigid_body_handle)
          .get_world_aabb();
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 0) {
        nen::aabb box_aabb;
        auto &act_e = GetScene().get_actor<nen::base_actor>(map_actors[i][j]);

        box_aabb.max = act_e.GetPosition() + act_e.GetScale();
        box_aabb.min = act_e.GetPosition() - act_e.GetScale();

        bool value = nen::collision::aabb_aabb(enemy_aabb, box_aabb);
        if (value) {
          SetPosition(before_pos);
          is_collied = true;
        }
      }
    }
  }
  return is_collied;
}