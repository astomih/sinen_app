#pragma once
#include <Nen/Nen.hpp>

class Title : public nen::base_scene {
public:
  Title();
  void Setup() override;
  void Update(float deltaTime) override;

private:
};