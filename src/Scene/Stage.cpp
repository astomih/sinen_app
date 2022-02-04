#include "Stage.hpp"
#include "../Actor/Camera.hpp"
#include "../model/model.hpp"
#include "Actor/Actor.hpp"
#include "Color/Color.hpp"
#include "Component/Draw2DComponent.hpp"
#include "Component/Draw3DComponent.hpp"
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
#include <DTL/DTL.hpp>
#include <Nen/Nen.hpp>
#include <memory>
#include <string>

const float scale = 5.f;

Stage::Stage() {}

void Stage::Setup() {
  model _model;
  _model.load("player.sim");
  _model.set(GetRenderer(), "player");
  auto pt = std::make_shared<nen::texture>();
  pt->CreateFromColor(nen::color(1, 1, 1, 1), "none");
  dtl::shape::SimpleRogueLike<uint32_t>(1, 1, 3, 4, 5, 2, 5, 2).draw(map);
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

  auto t = std::make_shared<nen::texture>();
  t->Load("rect.png");

  auto &pc = player.add_component<nen::draw_3d_component>();
  player.SetScale(nen::vector3(scale / 2.f));
  pc.Create(pt, "player");
  pc.Register();

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 1) {
        std::uint32_t k;
        auto &a = add_actor<nen::base_actor>(k);
        a.SetPosition(nen::vector3(j * scale * 2.f, -i * scale * 2.f, 0.f));
        a.SetScale(nen::vector3(scale));
        auto &c = a.add_component<nen::draw_3d_component>();
        c.Create(t);
        c.Register();
        map_actors[i][j] = k;
      }
      if (map[i][j] == 0) {
        std::uint32_t k;
        auto &a = add_actor<nen::base_actor>(k);
        a.SetPosition(nen::vector3(j * scale * 2.f, -i * scale * 2.f, 0.f));
        a.SetScale(nen::vector3(scale));
        auto &c = a.add_component<nen::draw_3d_component>();
        c.Create(t, "BOX");
        c.Register();
        map_actors[i][j] = k;
      }
    }
  }
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
