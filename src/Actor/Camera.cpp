#include "Camera.hpp"
#include <Nen/Nen.hpp>

CameraActor::CameraActor(nen::base_scene &scene)
    : base_actor(scene), verticalAngle(-nen::Math::Pi / 4.f), isfocusing(true) {
  initial_pos = nen::vector3(0.f, 10.f, 30.f);
  SetPosition(initial_pos);
  lookAt = nen::vector3(0.f, 0, -5.f);
  initial_lookAt = lookAt;
  nen::transform trans(*this);
  trans.LookAt(lookAt, nen::vector3::UnitY);
  auto view = nen::matrix4::LookAt(GetPosition(), lookAt, nen::vector3::UnitY);
  GetScene().GetRenderer()->SetViewMatrix(view);
}

void CameraActor::Update(float deltaTime) {
  /*
  float mouseSpeed = 0.05f;
  auto winsize = GetScene().GetRenderer()->GetWindow()->Size();
  auto window = GetScene().GetRenderer()->GetWindow();
  if (window->GetState() == WindowState::LEAVE)
          isfocusing = false;
  if (window->GetState() == WindowState::ENTER)
          isfocusing = true;
  if (isfocusing)
  {
          mouse = GetInput().Mouse.GetPosition();
          GetInput().Mouse.SetPosition(Vector2(winsize.x / 2.f, winsize.y
  / 2.f)); horizontalAngle += mouseSpeed * deltaTime * float(winsize.x / 2 -
  mouse.x);
  }
  else
  {
          mouse = Vector2::Zero;
  }
  //verticalAngle += mouseSpeed * deltaTime * float(Window::Size.y / 2 -
  mouse.y); direction = Vector3( Math::Cos(verticalAngle) *
  Math::Sin(horizontalAngle), Math::Sin(verticalAngle), Math::Cos(verticalAngle)
  * Math::Cos(horizontalAngle)); right = Vector3( Math::Sin(horizontalAngle -
  Math::PiOver2), 0, Math::Cos(horizontalAngle - Math::PiOver2)); up =
  Vector3::Cross(right, direction); Matrix4 view =
  Matrix4::LookAt(GetPosition(), GetPosition() + direction, up);
  GetScene().GetRenderer()->SetViewMatrix(view);
  */
  auto view = nen::matrix4::LookAt(GetPosition(), lookAt, nen::vector3::UnitY);
  GetScene().GetRenderer()->SetViewMatrix(view);
}
