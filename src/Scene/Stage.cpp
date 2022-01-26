#include "Stage.hpp"
#include "../Actor/Camera.hpp"
#include "../model/model.hpp"
#include "Actor/Actor.hpp"
#include "Component/Draw2DComponent.hpp"
#include "Component/Draw3DComponent.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Random.hpp"
#include "Math/Vector3.hpp"
#include "Script/Script.hpp"
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
  player->SetPosition(
      nen::vector3(scale * 2 * r2, -scale * 3.f, scale * 2 * r1));

  auto t = std::make_shared<nen::texture>();
  t->Load("rect.png");

  auto pt = std::make_shared<nen::texture>();
  pt->Load("base.png");
  camera = std::make_unique<CameraActor>(*this);
  auto pc = player->AddComponent<nen::draw_3d_component>();
  player->SetScale(nen::vector3(scale));
  pc->Create(pt, "player");
  pc->Register();

  auto act2 = AddActor<nen::base_actor>();
  act2->SetScale(nen::vector3(10.f, 10.f, 0.f));

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 1) {
        auto a = AddActor<nen::base_actor>();
        a->SetPosition(
            nen::vector3(j * scale * 2.f, -scale * 1.5f, i * scale * 2.f));
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
        a->SetPosition(nen::vector3(j * scale * 2.f, 0, i * scale * 2.f));
        a->SetScale(nen::vector3(scale));
        auto c = a->AddComponent<nen::draw_3d_component>();
        c->Create(t, "BOX");
        c->Register();
        map_actors[i][j] = a;
      }
    }
  }
}

nen::matrix4 screen_to_world(const nen::vector2 &m_pos) {}

void Stage::Update(float deltaTime) {
  { auto pos_mouse = GetInput().Mouse.GetPosition(); }
  if (GetInput().Keyboard.GetKeyState(nen::key_code::UP) ==
          nen::button_state::Held ||
      GetInput().Keyboard.GetKeyState((nen::key_code::K)) ==
          nen::button_state::Held) {
    auto before = player->GetPosition();
    player->Move(0, 0, -scale * 2.f * deltaTime);
    for (int i = 0; i < map.size(); i++) {
      for (int j = 0; j < map[i].size(); j++) {
        if (map[i][j] == 1 &&
            nen::collision::IntersectAABB(
                player->GetPosition(), map_actors[i][j]->GetPosition(),
                nen::vector3(scale * 1.5f, 0, scale))) {
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
    player->Move(0, 0, scale * 2.f * deltaTime);
    for (int i = 0; i < map.size(); i++) {
      for (int j = 0; j < map[i].size(); j++) {
        if (map[i][j] == 1 &&
            nen::collision::IntersectAABB(
                player->GetPosition(), map_actors[i][j]->GetPosition(),
                nen::vector3(scale * 1.5f, 0, scale))) {
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
        if (map[i][j] == 1 &&
            nen::collision::IntersectAABB(
                player->GetPosition(), map_actors[i][j]->GetPosition(),
                nen::vector3(scale * 1.5f, 0, scale))) {
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
        if (map[i][j] == 1 &&
            nen::collision::IntersectAABB(
                player->GetPosition(), map_actors[i][j]->GetPosition(),
                nen::vector3(scale * 1.5f, 0, scale))) {
          player->SetPosition(before);
        }
      }
    }
  }
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 1 &&
          nen::collision::IntersectAABB(player->GetPosition(),
                                        map_actors[i][j]->GetPosition(),
                                        nen::vector3(scale, 0, scale))) {
        map_actors[i][j]
            ->GetComponent<nen::draw_3d_component>()
            ->GetSprite()
            ->textureIndex = "White";
      }
    }
  }
  camera->SetPosition(player->GetPosition() + camera->initial_pos);
  camera->lookAt = player->GetPosition() + camera->initial_lookAt;
  camera->Update(deltaTime);
}
