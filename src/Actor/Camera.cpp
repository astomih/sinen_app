#include "Camera.hpp"
#include "GUI/Button.hpp"
#include "Input/InputSystem.hpp"
#include "Input/MouseCode.hpp"
#include "Math/Vector3.hpp"
#include "Window/Window.hpp"
#include "Window/WindowState.hpp"
#include <Nen/Nen.hpp>

CameraActor::CameraActor(nen::base_scene &scene)
    : base_actor(scene), verticalAngle(-nen::Math::Pi / 4.f), isfocusing(true) {
  initial_pos = nen::vector3(0, 20.f, 15.f);
  SetPosition(initial_pos);
  lookAt = nen::vector3(0.f, 0, -5.f);
  nen::transform trans(*this);
  trans.LookAt(lookAt, nen::vector3::UnitY);
  auto view = nen::matrix4::LookAt(GetPosition(), lookAt, nen::vector3::UnitY);
  GetScene().GetRenderer()->SetViewMatrix(view);
}

void CameraActor::Update(float deltaTime) {
  float mouseSpeed = 0.5f;
  auto winsize = GetScene().GetRenderer()->GetWindow()->Size();
  auto current_window = GetScene().GetRenderer()->GetWindow();
  if (current_window->GetState() == nen::window_state::LEAVE)
    isfocusing = false;
  if (current_window->GetState() == nen::window_state::ENTER)
    isfocusing = true;
  if (GetInput().Mouse.GetButtonState(nen::mouse_code::RIGHT) ==
      nen::button_state::Pressed)
    initial_mouse_pos = GetInput().Mouse.GetPosition();
  if (isfocusing && GetInput().Mouse.GetButtonState(nen::mouse_code::RIGHT) ==
                        nen::button_state::Held) {
    mouse = GetInput().Mouse.GetPosition();
    auto horizon =
        mouseSpeed * deltaTime * float(initial_mouse_pos.x - mouse.x);
    const float s = 0.05f;
    if (horizon > s)
      horizon = s;
    if (horizon < -s)
      horizon = -s;
    // horizontalAngle += horizon;
    auto vertical =
        mouseSpeed * deltaTime * float(initial_mouse_pos.y - mouse.y);
    if (vertical > s)
      vertical = s;
    if (vertical < -s)
      vertical = -s;
    verticalAngle += vertical;
    /*
    GetInput().Mouse.SetPosition(
        nen::vector2(winsize.x / 2.f, winsize.y / 2.f));
        */

  } else {
    mouse = nen::vector2::Zero;
  }
  direction = nen::vector3(
      nen::Math::Cos(verticalAngle) * nen::Math::Sin(horizontalAngle),
      nen::Math::Sin(verticalAngle),
      nen::Math::Cos(verticalAngle) * nen::Math::Cos(horizontalAngle));
  right = nen::vector3(nen::Math::Sin(horizontalAngle - nen::Math::PiOver2), 0,
                       nen::Math::Cos(horizontalAngle - nen::Math::PiOver2));
  up = nen::vector3::Cross(right, direction);
  auto view =
      nen::matrix4::LookAt(GetPosition(), GetPosition() + direction, up);
  GetScene().GetRenderer()->SetViewMatrix(view);
}
