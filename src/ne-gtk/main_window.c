#include "ne-gtk/window.h"
#include "services/netmusic.h"
#include "css/tab.h"
#include <curl/curl.h>
#include <curl/easy.h>
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtk/gtk.h>
#endif

static void recommend_clicked(const GtkButton *button, gpointer listbox) {
  (void)button;
  (void)listbox;
  struct mem_with_size mem = {0, 0};
  get_album_new(&mem);
  set_pop_album_to_listbox(&mem, GTK_LIST_BOX(listbox));
  // get_pop_album((GtkListBox*)listbox);
}


void main_window(const GApplication *app) {
  GtkWidget *window;
  GtkWidget *window_box;
  GtkWidget *tab;
  GtkWidget *tab_detail;
  GtkWidget *recommend;
  GtkWidget *discover;
  GtkWidget *home;
  GtkWidget *list_box;
  // GtkWidget *progress_bar;

  window = gtk_application_window_new(GTK_APPLICATION(app));
  gtk_window_set_title(GTK_WINDOW(window), "new-music");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

  window_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_window_set_child(GTK_WINDOW(window), window_box);

  tab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_set_homogeneous(GTK_BOX(tab), TRUE);
  gtk_box_append(GTK_BOX(window_box), tab);

  recommend = gtk_button_new_with_label("推荐");
  discover = gtk_button_new_with_label("发现");
  home = gtk_button_new_with_label("主页");

  tab_detail = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_hexpand(tab_detail, TRUE);
  gtk_widget_set_vexpand(tab_detail, TRUE);
  gtk_widget_set_halign(tab_detail, GTK_ALIGN_FILL);
  gtk_box_append(GTK_BOX(window_box), tab_detail);

  // list_box = gtk_grid_new();
  // gtk_grid_set_column_homogeneous(GTK_GRID(list_box), TRUE);
  list_box = gtk_list_box_new();
  gtk_widget_set_name(list_box, "popalbum-list");
  gtk_box_append(GTK_BOX(tab_detail), list_box);

  gtk_box_append(GTK_BOX(tab), recommend);
  gtk_box_append(GTK_BOX(tab), discover);
  gtk_box_append(GTK_BOX(tab), home);

  g_signal_connect(recommend, "clicked", G_CALLBACK(recommend_clicked),
                   list_box);
  gtk_window_present(GTK_WINDOW(window));
}