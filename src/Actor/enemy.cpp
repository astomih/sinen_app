#include "enemy.hpp"

void enemy_actor::Update(float delta_time) {
  float z = nen::Math::Sin0_1(2) * 2;
  if (z < 0.f)
    z = 0.f;
  SetPosition(nen::vector3(GetPosition().x, GetPosition().y, z));
}