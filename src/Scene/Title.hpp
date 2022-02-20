#pragma once
#include "Actor/Actor.hpp"
#include <Nen/Nen.hpp>
#include <cstdint>

class Title : public nen::base_scene {
public:
  Title(class nen::manager &_manager);
  void Setup() override;
  void Update(float deltaTime) override;

private:
  bool is_prepare_now_loading = false;
  uint32_t handle_title;
  uint32_t handle_utilis;
  uint32_t c1;
  uint32_t c2;
};