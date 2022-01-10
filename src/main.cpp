#include <Nen/Nen.hpp>

#include "Scene/Title.hpp"

void Main::Setup() { nen::ChangeScene(std::make_shared<Title>()); }

void Main::Update(float deltaTime) {}
