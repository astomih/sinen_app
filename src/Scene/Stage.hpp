#pragma once
#include "../Actor/Camera.hpp"
#include <Nen/Nen.hpp>
#include <array>

class Stage : public nen::base_scene {
public:
  Stage();
  void Setup() override;
  void Update(float deltaTime) override;

private:
  std::vector<std::vector<int>> map;
  std::vector<std::vector<std::shared_ptr<nen::base_actor>>> map_actors;
  std::shared_ptr<nen::base_actor> player;
  std::unique_ptr<CameraActor> camera;
  std::shared_ptr<nen::texture> white_tex;
};
