// #include <stdbool.h>
// #include <stdio.h>

// #include "services/netmusic.h"
#include "ne-gtk/window.h"
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtkmm.h>
#endif

auto main(int argc, char* argv[]) -> int
{
  const auto app = Gtk::Application::create("com.suoyuan.nemusicgtk");

  return app->make_window_and_run<new_gtk>(argc, argv);
}