#pragma once
#include <Nen/Nen.hpp>
class CameraActor : public nen::base_actor {
public:
  CameraActor(nen::base_scene &scene);

  void Update(float deltaTime) override;
  nen::vector3 initial_pos;
  nen::vector2 initial_mouse_pos;
  nen::vector3 initial_lookAt;
  nen::vector3 lookAt;
  nen::vector3 direction;
  nen::vector3 right;
  nen::vector3 up;
  // 水平角、-Z方向
  float horizontalAngle = nen::Math::Pi;
  // 鉛直角、0、水平線を眺めている
  float verticalAngle = 0.0f;
  bool isfocusing = true;
  nen::vector2 mouse;
};
