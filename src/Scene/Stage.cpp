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
  m_player = std::make_unique<player_actor>(*this);
  m_player->SetPosition(nen::vector3(scale * 2 * r2, -scale * 2 * r1, 0));

  auto t = std::make_shared<nen::texture>();
  t->Load("rect.png");

  auto pc = m_player->AddComponent<nen::draw_3d_component>();
  m_player->SetScale(nen::vector3(scale / 2.f));
  pc->Create(pt, "player");
  pc->Register();

  auto act2 = AddActor<nen::base_actor>();
  act2->SetScale(nen::vector3(10.f, 0.f, 10.f));

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 1) {
        auto a = AddActor<nen::base_actor>();
        a->SetPosition(
            nen::vector3(j * scale * 2.f, -i * scale * 2.f, -scale * 1.5f));
        a->SetScale(nen::vector3(scale));
        auto c = a->AddComponent<nen::draw_3d_component>();
        c->Create(t);
        c->Register();
        map_actors[i][j] = a;
      }
      if (map[i][j] == 0) {
        auto a = AddActor<nen::base_actor>();
        a->SetPosition(nen::vector3(j * scale * 2.f, -i * scale * 2.f, 0.f));
        a->SetScale(nen::vector3(scale));
        auto c = a->AddComponent<nen::draw_3d_component>();
        c->Create(t, "BOX");
        c->Register();
        map_actors[i][j] = a;
      }
    }
  }
  auto camera = add_actor2<CameraActor>(camera_handle);
  camera.SetPosition(m_player->GetPosition() + camera.initial_pos);
  camera.lookAt = m_player->GetPosition() - camera.initial_lookAt;
  camera.Update(0.f);
}

void Stage::Update(float deltaTime) {
#if 1
  static nen::quaternion init_rotate = m_player->GetRotation();
  auto camera = get_actor2<CameraActor>(camera_handle);
  camera.SetPosition(m_player->GetPosition() + camera.initial_pos);
  camera.lookAt = m_player->GetPosition() - camera.initial_lookAt;
  m_player->update_move(deltaTime, map, map_actors);
  m_player->UpdateActor(deltaTime);
#endif
}
