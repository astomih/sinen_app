#pragma once

#include <Nen.hpp>
#include <cstdint>
#include <memory>
#include <vector>
class bullet_actor : public nen::base_actor {
public:
  bullet_actor(nen::base_scene &scene, std::vector<uint32_t> &bullets);
  void set_speed(float speed) { m_speed = speed; }
  void set_dead_time(float dead_time) { m_dead_time = dead_time; }
  void set_this_handle(uint32_t handle) { m_handle = handle; }
  void Update(float delta_time) override;

private:
  std::vector<uint32_t> &m_bullets;
  uint32_t m_handle;
  float m_speed;
  float m_dead_time;
  float m_current_time;
};
