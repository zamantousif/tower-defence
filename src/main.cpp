#include <SFML/Graphics.hpp>
#include "application.hpp"

int main() {
  td::Application* app = new td::Application();
  app->run();
  delete(app);
  return 0;
}
