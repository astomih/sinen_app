#include "bullet.hpp"
#include "Actor/Actor.hpp"
#include "Component/Draw3DComponent.hpp"
#include "Scene/Scene.hpp"
#include "Utility/dynamic_handler.hpp"
#include <memory>
#include <vector>

bullet_actor::bullet_actor(nen::base_scene &scene,
                           std::vector<uint32_t> &bullets)
    : nen::base_actor(scene), m_bullets(bullets) {
  nen::handle_t handle;
  auto &c = add_component<nen::draw_3d_component>(handle);
  c.Create(nullptr, "bullet");
  c.Register();
}

void bullet_actor::Update(float delta_time) {
  m_current_time += delta_time;
  if (m_current_time > m_dead_time) {
    SetState(nen::base_actor::state::Dead);
  }
  Move(GetForward() * m_speed * delta_time);
}