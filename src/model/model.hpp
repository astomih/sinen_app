#pragma once
#include <Nen.hpp>
#include <string_view>

class model {
public:
  model() = default;
  ~model() = default;

  void load(std::string_view str);
  void set(nen::renderer &_renderer, std::string_view name);

private:
  nen::vertex_array m_array;
};