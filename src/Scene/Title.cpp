#include "Title.hpp"
#include "Stage.hpp"
#include <Nen/Nen.hpp>

Title::Title() {}

void Title::Setup() {
  auto mplus_72 = std::make_shared<nen::font>();
  if (!mplus_72->LoadFromFile("mplus/mplus-1p-medium.ttf", 72))
    return;
  auto mplus_ = std::make_shared<nen::font>();
  if (!mplus_->LoadFromFile("mplus/mplus-1p-medium.ttf", 50))
    return;
  auto &titleText =
      add_actor<nen::base_actor>().add_component<nen::text_component>();
  titleText.SetFont(mplus_72);
  titleText.SetString("UTILIS", nen::palette::White);
  titleText.Register();

  auto &act1 = add_actor<nen::base_actor>();
  act1.SetPosition(nen::vector3(0, -50, 0));

  auto &playtext = act1.add_component<nen::text_component>();
  playtext.SetFont(mplus_);
  playtext.SetString("START");
  playtext.Register();
}

void Title::Update(float deltaTime) {
  if (GetInput().Keyboard.GetKeyState(nen::key_code::SPACE) ==
      nen::button_state::Pressed) {
    nen::ChangeScene(std::make_unique<Stage>());
  }
}
