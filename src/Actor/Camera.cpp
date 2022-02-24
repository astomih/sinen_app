#include "Camera.hpp"
#include <Nen/Nen.hpp>
#include <sol/sol.hpp>
CameraActor::CameraActor(nen::base_scene &scene)
    : base_actor(scene), verticalAngle(nen::Math::Pi / 4.f), isfocusing(true) {
  // initial_pos = nen::vector3{0, -15.f, 20.f};
  initial_pos = nen::vector3{0, -15.f, 15.f};
  SetPosition(initial_pos);
  initial_lookAt = nen::vector3{0.f, 5.f, 0};
  lookAt = initial_lookAt;

  auto view = nen::matrix4::LookAt(GetPosition(), lookAt, nen::vector3::UnitZ);
  GetScene().GetRenderer().SetViewMatrix(view);
}

void CameraActor::Update(float deltaTime) {
  constexpr float speed = 0.1f;
  auto &current_window = GetScene().GetRenderer().GetWindow();
  if (GetInput().Keyboard.GetKeyState(nen::key_code::LCTRL) ==
      nen::button_state::Held) {
    if (GetInput().Keyboard.GetKeyState(nen::key_code::UP) ==
        nen::button_state::Held) {

      verticalAngle += speed * deltaTime;
    }
    if (GetInput().Keyboard.GetKeyState(nen::key_code::DOWN) ==
        nen::button_state::Held) {
      verticalAngle -= speed * deltaTime;
    }
    if (GetInput().Keyboard.GetKeyState(nen::key_code::LEFT) ==
        nen::button_state::Held) {
      horizontalAngle += speed * deltaTime;
    }
    if (GetInput().Keyboard.GetKeyState(nen::key_code::RIGHT) ==
        nen::button_state::Held) {
      horizontalAngle -= speed * deltaTime;
    }
  }
  direction = nen::vector3{
      nen::Math::Cos(verticalAngle) * nen::Math::Sin(horizontalAngle),
      nen::Math::Sin(verticalAngle),
      nen::Math::Cos(verticalAngle) * nen::Math::Cos(horizontalAngle)};
  right = nen::vector3(nen::Math::Sin(horizontalAngle - nen::Math::PiOver2), 0,
                       nen::Math::Cos(horizontalAngle - nen::Math::PiOver2));
  up = nen::vector3::Cross(right, direction);
  auto view =
      nen::matrix4::LookAt(GetPosition(), GetPosition() + direction, up);
  GetScene().GetRenderer().SetViewMatrix(view);
}
