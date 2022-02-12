#include "Stage.hpp"
#include "../Actor/Camera.hpp"
#include "../Actor/enemy.hpp"
#include "../dungeon/generator.hpp"
#include "../model/model.hpp"
#include "Actor/Actor.hpp"
#include "Color/Color.hpp"
#include "Component/Draw2DComponent.hpp"
#include "Component/Draw3DComponent.hpp"
#include "DrawObject/ObjectType.hpp"
#include "Logger/Logger.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Matrix4.hpp"
#include "Math/Random.hpp"
#include "Math/Vector3.hpp"
#include "Scene/Scene.hpp"
#include "Script/Script.hpp"
#include "Texture/Texture.hpp"
#include "Vertex/Vertex.hpp"
#include "Vertex/VertexArray.hpp"
#include "instancing/instance_data.hpp"
#include "instancing/instancing.hpp"
#include <Nen/Nen.hpp>
#include <memory>
#include <string>

const float scale = 5.f;

Stage::Stage() {}

void Stage::Setup() {
  nen::random::Init();
  map.resize(map_size.second);
  for (size_t i = 0; i < map.size(); i++) {
    map[i].resize(map_size.first);
  }
  dungeon_generator<uint32_t> generator;
  generator.generate(map);
  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map[i].size(); j++) {
      std::cout << map[i][j];
    }
    std::cout << std::endl;
  }

  model _model;
  _model.load("player.sim");
  _model.set(GetRenderer(), "player");
  model spider;
  spider.load("spider.sim");
  spider.set(GetRenderer(), "spider");
  auto pt = std::make_shared<nen::texture>();
  pt->CreateFromColor(nen::color(1, 1, 1, 1), "none");

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
  auto &enemy_draw3d = enemy.add_component<nen::draw_3d_component>();
  enemy_draw3d.Create(pt, "spider");
  //  enemy_draw3d.Register();

  auto t = std::make_shared<nen::texture>();
  t->Load("rect.png");

  auto &pc = player.add_component<nen::draw_3d_component>();
  player.SetScale(nen::vector3(scale / 2.f));
  pc.Create(pt, "player");
  pc.Register();
  bool is_once = true;
  bool is_once2 = true;

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 1) {
        std::uint32_t k;
        auto &a = add_actor<nen::base_actor>(k);
        a.SetPosition(nen::vector3(j * scale * 2.f, -i * scale * 2.f, -scale));
        a.SetScale(nen::vector3(scale));
        if (is_once) {
          auto &c = a.add_component<nen::draw_3d_component>();
          c.Create(t);
          sprite_instancing.object = c.GetSprite();
          is_once = false;
        } else {
          auto &c = a.add_component<nen::draw_3d_component>();
          c.Create(t);
        }
        nen::instance_data data;
        auto m = a.GetWorldTransform();
        int l = 0;
        for (int i = 0; i < 4; i++) {
          data.world_matrix_1[i] = m.mat[l][i];
        }
        l++;
        for (int i = 0; i < 4; i++) {
          data.world_matrix_2[i] = m.mat[l][i];
        }
        l++;
        for (int i = 0; i < 4; i++) {
          data.world_matrix_3[i] = m.mat[l][i];
        }
        l++;
        for (int i = 0; i < 4; i++) {
          data.world_matrix_4[i] = m.mat[l][i];
        }
        sprite_instancing.data.push_back(data);

        map_actors[i][j] = k;
      }
      if (map[i][j] == 0) {
        std::uint32_t k;
        auto &a = add_actor<nen::base_actor>(k);
        a.SetPosition(nen::vector3(j * scale * 2.f, -i * scale * 2.f, 0.f));
        a.SetScale(nen::vector3(scale));
        if (is_once2) {
          auto &c = a.add_component<nen::draw_3d_component>();
          c.Create(t, "BOX");
          box_instancing.object = c.GetSprite();
          is_once2 = false;
        } else {
          auto &c = a.add_component<nen::draw_3d_component>();
          c.Create(t, "BOX");
        }
        nen::instance_data data;
        auto m = a.GetWorldTransform();
        int l = 0;
        for (int i = 0; i < 4; i++) {
          data.world_matrix_1[i] = m.mat[l][i];
        }
        l++;
        for (int i = 0; i < 4; i++) {
          data.world_matrix_2[i] = m.mat[l][i];
        }
        l++;
        for (int i = 0; i < 4; i++) {
          data.world_matrix_3[i] = m.mat[l][i];
        }
        l++;
        for (int i = 0; i < 4; i++) {
          data.world_matrix_4[i] = m.mat[l][i];
        }
        box_instancing.data.push_back(data);
        map_actors[i][j] = k;
      }
    }
  }
  sprite_instancing._texture = t;
  sprite_instancing.size =
      sizeof(nen::instance_data) * sprite_instancing.data.size();
  sprite_instancing.type = nen::object_type::_3D;
  GetRenderer()->add_instancing(sprite_instancing);

  box_instancing._texture = t;
  box_instancing.size = sizeof(nen::instance_data) * box_instancing.data.size();
  box_instancing.type = nen::object_type::_3D;
  GetRenderer()->add_instancing(box_instancing);

  auto &camera = add_actor<CameraActor>(handle_camera);
  camera.SetPosition(player.GetPosition() + camera.initial_pos);
  camera.lookAt = player.GetPosition() - camera.initial_lookAt;
  camera.Update(0.f);
}

void Stage::Update(float deltaTime) {
  auto &camera = get_actor<CameraActor>(handle_camera);
  auto &player = get_actor<player_actor>(handle_player);
  camera.SetPosition(player.GetPosition() + camera.initial_pos);
  camera.lookAt = player.GetPosition() - camera.initial_lookAt;
  camera.Update(deltaTime);
  player.update_move(deltaTime, map, map_actors);
}
