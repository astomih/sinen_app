#pragma once
#include "Render/Renderer.hpp"
#include "Vertex/VertexArray.hpp"
#include <string_view>

class model {
public:
  model() = default;
  ~model() = default;

  void load(std::string_view str);
  void set(std::shared_ptr<nen::renderer> _renderer, std::string_view name);

private:
  nen::vertex_array m_array;
};