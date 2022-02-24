#if 1
#include "Title.hpp"
#include "Stage.hpp"
#include <Nen/Nen.hpp>
#include <sinen_lua.hpp>

Title::Title(nen::manager &_manager) : nen::base_scene(_manager) {}

void Title::Setup() {
  nen::load_modules(get_script().get_sol_state());
  auto mplus_72 = std::make_shared<nen::font>();
  if (!mplus_72->LoadFromFile("mplus/mplus-1p-medium.ttf", 72))
    return;
  auto mplus_ = std::make_shared<nen::font>();
  if (!mplus_->LoadFromFile("mplus/mplus-1p-medium.ttf", 50))
    return;
  auto &titleText = add_actor<nen::base_actor>(handle_utilis)
                        .add_component<nen::text_component>(c1);
  titleText.SetFont(mplus_72);
  titleText.SetString("singa", nen::palette::White);
  titleText.Register();

  auto &act1 = add_actor<nen::base_actor>(handle_title);
  act1.SetPosition(nen::vector3(0, -80, 0));

  auto &playtext = act1.add_component<nen::text_component>(c2);
  playtext.SetFont(mplus_);
  playtext.SetString("PRESS SPACE OR CLICK TO START", nen::palette::White);
  playtext.Register();
}

void Title::Update(float deltaTime) {
  // if (is_prepare_now_loading)
  // change_scene(std::make_unique<Stage>(get_manager()));

  if (GetInput().Keyboard.GetKeyState(nen::key_code::SPACE) ==
          nen::button_state::Pressed ||
      GetInput().Mouse.GetButtonState(nen::mouse_code::LEFT) ==
          nen::button_state::Pressed) {

    auto mplus_72 = std::make_shared<nen::font>();
    if (!mplus_72->LoadFromFile("mplus/mplus-1p-medium.ttf", 72))
      return;
    nen::handle_t handle;
    auto &titleText =
        add_actor<nen::base_actor>(handle).add_component<nen::text_component>(
            handle);
    titleText.SetFont(mplus_72);
    titleText.SetString("Now Loading ...", nen::palette::White);
    titleText.Register();
    is_prepare_now_loading = true;
    get_actor<nen::base_actor>(handle_utilis).remove_component(c1);
    get_actor<nen::base_actor>(handle_title).remove_component(c2);
  }
}
#endif