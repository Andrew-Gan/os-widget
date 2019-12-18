#include <gtkmm/application.h>
#include "panel.h"

int main (int argc, char* argv[]) {
  // create new GUI interface
  auto app = Gtk::Application::create(argc, argv, "os.activity.widget");
  MainPanel panel;

  // execute widget application
  return app->run(panel);
}
