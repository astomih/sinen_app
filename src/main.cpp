#include <Nen/Nen.hpp>
#include <sinen_lua.hpp>

int main(int argc, char *argv[]) {
  nen::manager manager;
  if (!manager.initialize())
    return -1;
  nen::load_modules(manager.get_script_system().get_sol_state());
  manager.launch();
  return 0;
}