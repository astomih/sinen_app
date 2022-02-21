#include "enemy.hpp"
#include "Component/rigidbody_component.hpp"
#include "Logger/Logger.hpp"
#include "Math/Matrix4.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Vector3.hpp"
enemy_actor::enemy_actor(nen::base_scene &scene, map_t &map,
                         map_actors_t &map_actors)
    : nen::base_actor(scene), map(map), map_actors(map_actors) {}

void enemy_actor::Update(float delta_time) {
  float z = nen::Math::Sin0_1(2) * 2;
  if (z < 0.f)
    z = 0.f;
  SetPosition(nen::vector3(GetPosition().x, GetPosition().y, z));
}

void enemy_actor::move_to_player(float dt, const player_actor &player) {
  auto player_pos = player.GetPosition();
  auto before = GetPosition();
  auto dir = player_pos - before;
  dir.Normalize();
  dir *= 10.f * dt;
  nen::quaternion q(nen::vector3::UnitZ, -nen::Math::Atan2(dir.x, dir.y));
  SetRotation(q);
  Move(dir);
  get_component<nen::rigidbody_component>(rigid_body_handle).Update(dt);
  if (collision(before, map, map_actors, player)) {
    Move(dir.x, 0, 0);
    if (!collision(before, map, map_actors, player))
      return;
    Move(0, dir.y, 0);
    collision(before, map, map_actors, player);
  }
}

bool enemy_actor::collision(const nen::vector3 &before_pos, const map_t &map,
                            const map_actors_t &map_actors,
                            const player_actor &player) {
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