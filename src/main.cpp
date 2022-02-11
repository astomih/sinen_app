#include "Scene/Stage.hpp"
#include <Nen/Nen.hpp>

int main(int argc, char *argv[]) {
  nen::manager manager;
  manager.launch(std::make_unique<Stage>());
  return 0;
}