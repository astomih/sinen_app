#include "Stage.hpp"
#include "../Actor/Camera.hpp"
#include "../Actor/enemy.hpp"
#include "../dungeon/generator.hpp"
#include "../model/model.hpp"
#include "Component/rigidbody_component.hpp"
#include "Scene/Scene.hpp"
#include <Nen/Nen.hpp>
#include <cstdint>
#include <memory>
#include <string>

const float scale = 5.f;

Stage::Stage(nen::manager &_manager) : nen::base_scene(_manager) {}

void Stage::prepare_model() {
  player_model.load("player.sim");
  player_model.set(GetRenderer(), "player");

  spider_model.load("spider.sim");
  spider_model.set(GetRenderer(), "spider");
  model wall;
  wall.load("wall_box.sim");
  wall.set(GetRenderer(), "wall_box");
  model bullet_model;
  bullet_model.load("bullet.sim");
  bullet_model.set(GetRenderer(), "bullet");
}

void Stage::prepare_dungeon() {
  nen::random::Init();
  map.resize(map_size.second);
  for (size_t i = 0; i < map.size(); i++) {
    map[i].resize(map_size.first);
  }
  dungeon_generator<uint32_t> generator;
  generator.generate(map);
  /*
  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map[i].size(); j++) {
      std::cout << map[i][j];
    }
    std::cout << std::endl;
  }
  */
}
void Stage::prepare_texture() {
  player_texture = std::make_shared<nen::texture>();
  player_texture->CreateFromColor(nen::color(1, 1, 1, 1), "none");
}

void Stage::prepare_actor() {
  int r1, r2;
  auto decide_ppos = [&]() {
    r1 = nen::random::GetIntRange(0, map_size.first - 1);
    r2 = nen::random::GetIntRange(0, map_size.second - 1);
    return map[r1][r2] == 1;
  };
  while (!decide_ppos()) {
  }
  auto &player = add_actor<player_actor>(handle_player, 1, 2);
  player.SetPosition(nen::vector3(scale * 2 * r2, -scale * 2 * r1, 0));

  auto &enemy = add_actor<enemy_actor>(handle_enemy, map, map_actors);
  while (!decide_ppos()) {
  }
  enemy.SetPosition(nen::vector3(scale * 2 * r2, -scale * 2 * r1, 0));
  bool is_once = true;
  bool is_once2 = true;
  auto t = std::make_shared<nen::texture>();
  t->Load("rect.png");

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 1) {
        std::uint32_t k;
        auto &a = add_actor<nen::base_actor>(k);
        a.SetPosition(nen::vector3(j * scale * 2.f, -i * scale * 2.f, -scale));
        a.SetScale(nen::vector3(scale));
        if (is_once) {
          uint32_t h;
          auto &c = a.add_component<nen::draw_3d_component>(h);
          c.Create(t);
          sprite_instancing.object = c.GetSprite();
          is_once = false;
        } else {
          uint32_t h;
          auto &c = a.add_component<nen::draw_3d_component>(h);
          c.Create(t);
          a.remove_component(h);
        }
        nen::instance_data data;
        auto m = a.GetWorldTransform();
        sprite_instancing.world_to_instance_data(m, data);
        sprite_instancing.data.push_back(data);

        map_actors[i][j] = k;
      }
      if (map[i][j] == 0) {
        std::uint32_t k;
        auto &a = add_actor<nen::base_actor>(k);
        a.SetPosition(nen::vector3(j * scale * 2.f, -i * scale * 2.f, 0.f));
        a.SetScale(nen::vector3(scale));
        if (is_once2) {
          nen::handle_t h;
          auto &c = a.add_component<nen::draw_3d_component>(h);
          c.Create(player_texture, "wall_box");
          box_instancing.object = c.GetSprite();
          is_once2 = false;
        } else {
          nen::handle_t h;
          auto &c = a.add_component<nen::draw_3d_component>(h);
          c.Create(player_texture, "wall_box");
        }
        nen::instance_data data;
        auto m = a.GetWorldTransform();
        box_instancing.world_to_instance_data(m, data);
        box_instancing.data.push_back(data);
        map_actors[i][j] = k;
      }
    }
  }
  nen::handle_t h;
  auto &enemy_draw3d = enemy.add_component<nen::draw_3d_component>(h);
  enemy_draw3d.Create(player_texture, "spider");
  enemy_draw3d.Register();
  auto &rigid_body_handle = enemy.add_component<nen::rigidbody_component>(h);
  rigid_body_handle.set_local_aabb(spider_model.m_aabb);
  enemy.rigid_body_handle = h;

  player.set_aabb(player_model.m_aabb);
  auto &pc = player.add_component<nen::draw_3d_component>(h);
  player.SetScale(nen::vector3(scale / 2.f));
  pc.Create(player_texture, "player");
  pc.Register();
  sprite_instancing._texture = t;
  sprite_instancing.size =
      sizeof(nen::instance_data) * sprite_instancing.data.size();
  sprite_instancing.type = nen::object_type::_3D;
  GetRenderer().add_instancing(sprite_instancing);

  box_instancing._texture = t;
  box_instancing.size = sizeof(nen::instance_data) * box_instancing.data.size();
  box_instancing.type = nen::object_type::_3D;
  GetRenderer().add_instancing(box_instancing);

  auto &camera = add_actor<CameraActor>(handle_camera);
  camera.SetPosition(player.GetPosition() + camera.initial_pos);
  camera.lookAt = player.GetPosition() - camera.initial_lookAt;
  camera.Update(0.f);
}
void Stage::Setup() {
  auto &lua = get_manager().get_script_system().get_sol_state();
  lua.new_usertype<nen::quaternion>(
      // type name
      "quat",
      // constructor
      sol::constructors<sol::types<>, sol::types<nen::vector3, float>>(),
      // member function
      "concatenate", &nen::quaternion::Concatenate,
      // data member
      "x", &nen::quaternion::x, "y", &nen::quaternion::y, "z",
      &nen::quaternion::z);
  prepare_model();
  prepare_dungeon();
  prepare_texture();
  prepare_actor();
}

void Stage::Update(float deltaTime) {
  auto &camera = get_actor<CameraActor>(handle_camera);
  auto &player = get_actor<player_actor>(handle_player);
  auto &enemy = get_actor<enemy_actor>(handle_enemy);
  camera.SetPosition(player.GetPosition() + camera.initial_pos);
  camera.lookAt = player.GetPosition() - camera.initial_lookAt;
  camera.Update(deltaTime);
  player.update_move(deltaTime, map, map_actors);
  player.update_bullet(m_bullets);
  enemy.move_to_player(deltaTime, player);
}
