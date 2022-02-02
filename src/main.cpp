#include "Scene/Title.hpp"
#include <Nen/Nen.hpp>

int main(int argc, char *argv[]) {
  nen::Launch(std::make_shared<Title>());
  return 0;
}