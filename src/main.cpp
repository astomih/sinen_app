#include "Scene/Stage.hpp"
#include "Scene/Title.hpp"
#include <Nen/Nen.hpp>

int main(int argc, char *argv[]) {
  nen::manager manager;
  manager.launch(std::make_unique<Title>(manager));
  return 0;
}