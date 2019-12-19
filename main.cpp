#include <gtkmm/application.h>
#include "panel.h"

int main (int argc, char* argv[]) {
  // ensure windows drive is mounted
  system("sudo mount -t ntfs-3g -o ro /dev/nvme0n1p3 /media/andrew-gan/Acer > /dev/null 2>&1");

  // create new GUI interface
  auto app = Gtk::Application::create(argc, argv, "os.activity.widget");
  MainPanel panel;

  // execute widget application
  return app->run(panel);
}
