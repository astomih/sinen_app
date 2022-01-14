#include <Nen/Nen.hpp>
#include "Scene/Title.hpp"

int main(int argc, char *argv[]) {
    nen::Launch(std::make_shared<Title>());
    nen::singleton_finalizer::Finalize();
    return 0;
}