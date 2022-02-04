#include "Scene/Title.hpp"
#include <Nen/Nen.hpp>

int main(int argc, char *argv[]) {
  nen::Launch(std::make_unique<Title>());
  return 0;
}