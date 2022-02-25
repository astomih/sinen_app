#include <Nen/Nen.hpp>
#include <sinen_lua.hpp>

int main(int argc, char *argv[]) {
  if (!nen::get_manager().initialize())
    return -1;
  nen::load_modules(nen::get_manager().get_script_system().get_sol_state());
  nen::get_manager().launch();
  return 0;
}