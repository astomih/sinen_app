#include <Nen/Nen.hpp>
#include <sinen_lua.hpp>

int main(int argc, char *argv[]) {
  if (!nen::initialize())
    return -1;
  nen::load_modules(nen::get_script_system().get_sol_state());
  nen::launch();
  return 0;
}