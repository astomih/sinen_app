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
  nen::script::DoScript("test.lua");
  _model.load("player.sim");
  _model.set(GetRenderer(), "player");
  auto pt = std::make_shared<nen::texture>();

  pt->CreateFromColor(nen::color(1, 1, 1, 1), "none");
  {
    auto c =
        AddActor<nen::base_actor>()->AddComponent<nen::draw_3d_component>();
    c->Create(pt, "player");
    c->Register();
  }

  dtl::shape::SimpleRogueLike<uint32_t>(1, 1, 3, 4, 5, 2, 5, 2).draw(map);
  player = AddActor<nen::base_actor>();
  int r1, r2;
  auto decide_ppos = [&]() {
    r1 = nen::random::GetIntRange(0, map_size.first - 1);
    r2 = nen::random::GetIntRange(0, map_size.second - 1);
    return map[r1][r2] == 1;
  };
  while (!decide_ppos()) {
  }
  player->SetPosition(nen::vector3(scale * 2 * r2, -scale * 2 * r1, 0));

  auto t = std::make_shared<nen::texture>();
  t->Load("rect.png");

  camera = std::make_unique<CameraActor>(*this);
  auto pc = player->AddComponent<nen::draw_3d_component>();
  player->SetScale(nen::vector3(scale));
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
        a->SetRotation(
            nen::quaternion(nen::vector3::UnitX, -nen::Math::PiOver2));
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
}

nen::vector3 screen_to_world(nen::base_scene *scene,
                             const nen::vector2 &m_pos) {
  nen::matrix4 m = nen::matrix4::Identity;
  auto windowsize = scene->GetRenderer()->GetWindow()->Size();
  m[3][0] = m_pos.x / windowsize.x;
  m[3][1] = (windowsize.y - m_pos.y) / windowsize.y;
  auto view = scene->GetRenderer()->GetViewMatrix();
  auto proj = scene->GetRenderer()->GetProjectionMatrix();

  m = m * view * proj;
  m.Invert();
  return m.GetTranslation();
}

void Stage::Update(float deltaTime) {
  if (GetInput().Keyboard.GetKeyState(nen::key_code::UP) ==
          nen::button_state::Held ||
      GetInput().Keyboard.GetKeyState((nen::key_code::K)) ==
          nen::button_state::Held) {
    auto before = player->GetPosition();
    player->Move(0, scale * 2.f * deltaTime, 0);
    for (int i = 0; i < map.size(); i++) {
      for (int j = 0; j < map[i].size(); j++) {
        if (map[i][j] == 0 &&
            nen::collision::IntersectAABB(
                player->GetPosition(), map_actors[i][j]->GetPosition(),
                nen::vector3(scale * 1.5f, scale, 0))) {
          player->SetPosition(before);
        }
      }
    }
  }
  if (GetInput().Keyboard.GetKeyState(nen::key_code::DOWN) ==
          nen::button_state::Held ||
      GetInput().Keyboard.GetKeyState((nen::key_code::J)) ==
          nen::button_state::Held) {
    auto before = player->GetPosition();
    player->Move(0, -scale * 2.f * deltaTime, 0);
    for (int i = 0; i < map.size(); i++) {
      for (int j = 0; j < map[i].size(); j++) {
        if (map[i][j] == 0 &&
            nen::collision::IntersectAABB(
                player->GetPosition(), map_actors[i][j]->GetPosition(),
                nen::vector3(scale * 1.5f, scale, 0))) {
          player->SetPosition(before);
        }
      }
    }
  }
  if (GetInput().Keyboard.GetKeyState(nen::key_code::LEFT) ==
          nen::button_state::Held ||
      GetInput().Keyboard.GetKeyState((nen::key_code::H)) ==
          nen::button_state::Held) {
    auto before = player->GetPosition();
    player->Move(-scale * 2.f * deltaTime, 0, 0);
    for (int i = 0; i < map.size(); i++) {
      for (int j = 0; j < map[i].size(); j++) {
        if (map[i][j] == 0 &&
            nen::collision::IntersectAABB(
                player->GetPosition(), map_actors[i][j]->GetPosition(),
                nen::vector3(scale * 1.5f, scale, 0))) {
          player->SetPosition(before);
        }
      }
    }
  }
  if (GetInput().Keyboard.GetKeyState(nen::key_code::RIGHT) ==
          nen::button_state::Held ||
      GetInput().Keyboard.GetKeyState((nen::key_code::L)) ==
          nen::button_state::Held) {
    auto before = player->GetPosition();
    player->Move(scale * 2.f * deltaTime, 0, 0);
    for (int i = 0; i < map.size(); i++) {
      for (int j = 0; j < map[i].size(); j++) {
        if (map[i][j] == 0 &&
            nen::collision::IntersectAABB(
                player->GetPosition(), map_actors[i][j]->GetPosition(),
                nen::vector3(scale * 1.5f, scale, 0))) {
          player->SetPosition(before);
        }
      }
    }
  }
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 0 &&
          nen::collision::IntersectAABB(player->GetPosition(),
                                        map_actors[i][j]->GetPosition(),
                                        nen::vector3(scale, scale, 0))) {
        map_actors[i][j]
            ->GetComponent<nen::draw_3d_component>()
            ->GetSprite()
            ->textureIndex = "White";
      }
    }
  }
  camera->SetPosition(player->GetPosition() + camera->initial_pos);
  camera->lookAt = player->GetPosition() - camera->initial_lookAt;
  camera->Update(deltaTime);
}
