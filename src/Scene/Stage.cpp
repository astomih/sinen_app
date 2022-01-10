#include "Stage.hpp"

#include <Nen/Nen.hpp>
#include <memory>

#include "../Actor/Camera.hpp"

const float scale = 5.f;

Stage::Stage() {}

void Stage::Setup() {
  player = AddActor<nen::base_actor>();
  player->SetPosition(nen::vector3(10, 0, 10));

  map = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
  map_actors.resize(map.size());
  for (int i = 0; i < map_actors.size(); i++) {
    map_actors[i].resize(map[i].size());
  }
  auto t = std::make_shared<nen::texture>();
  t->Load("rect.png");

  auto pt = std::make_shared<nen::texture>();
  pt->Load("player.png");
  camera = std::make_unique<CameraActor>(*this);
  auto pc = player->AddComponent<nen::draw_3d_component>();
  player->SetScale(nen::vector3(scale));
  pc->Create(pt);
  pc->Register();

  white_tex = std::make_shared<nen::texture>();
  white_tex->CreateFromColor(nen::palette::Blue, "White");

  auto act2 = AddActor<nen::base_actor>();
  act2->SetScale(nen::vector3(10.f, 10.f, 0.f));
  auto test = act2->AddComponent<nen::draw_2d_component>();
  test->Create(white_tex);
  test->Register();

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map.size(); j++) {
      if (map[i][j] == 0) {
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
      if (map[i][j] == 1) {
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

void Stage::Update(float deltaTime) {
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
