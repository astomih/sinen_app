#include "model.hpp"
#include "IO/AssetReader.hpp"
#include "IO/AssetType.hpp"
#include "Vertex/Vertex.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <sstream>
#include <string>

enum class load_state { version, vertex, indices };

void model::load(std::string_view str) {
  std::stringstream data;
  data << nen::asset_reader::LoadAsString(nen::asset_type::Model, str);
  std::string line;
  load_state state = load_state::version;
  std::string version;
  std::size_t index;
  while (std::getline(data, line)) {
    switch (state) {
    case load_state::version:
      if (line.starts_with("version ")) {
        version = line.substr(8, 5);
      } else if (line.starts_with("begin vertex")) {
        state = load_state::vertex;
      } else {
        std::cerr << "invalid formats." << std::endl;
      }
      break;
    case load_state::vertex: {
      if (line.starts_with("end vertex"))
        break;
      if (line.starts_with("begin indices"))
        state = load_state::indices;

      nen::vertex v;
      sscanf(line.data(), "%f %f %f %f %f %f %f %f %f %f %f %f\n",
             &v.position.x, &v.position.y, &v.position.z, &v.normal.x,
             &v.normal.y, &v.normal.z, &v.uv.x, &v.uv.y, &v.color.r, &v.color.g,
             &v.color.b, &v.color.a);

      m_array.vertices.push_back(v);
    } break;
    case load_state::indices: {

      if (line.starts_with("end vertex"))
        break;

      uint32_t i;
      sscanf(line.data(), "%u\n", &i);
      m_array.indices.push_back(i);
    } break;
    default:
      break;
    }
  }
  m_array.indexCount = m_array.indices.size();
  std::cout << "sim version: " + version << std::endl;
}
void model::set(std::shared_ptr<nen::renderer> _renderer,
                std::string_view name) {
  _renderer->AddVertexArray(m_array, name);
}