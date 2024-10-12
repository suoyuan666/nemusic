#include <stdbool.h>
#include <stdio.h>

#include "services/netmusic.h"
#include "ne-gtk/window.h"
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtk/gtk.h>
#endif

int main(int argc, char *argv[]) {
  GtkApplication *app;
  int stat;

  app = gtk_application_new("com.suoyuan.newmusic", G_APPLICATION_HANDLES_OPEN);
  g_signal_connect(app, "activate", G_CALLBACK(main_window), NULL);
  stat = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return stat;
}
