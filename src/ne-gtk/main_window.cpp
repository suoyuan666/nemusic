#include <memory>
#include "ne-gtk/window.h"
#include "sigc++/functors/mem_fun.h"
#include "services/netmusic.h"
// #include "css/tab.h"
// #include <curl/curl.h>
// #include <curl/easy.h>
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtkmm.h>
#endif


auto new_gtk::recommend_clicked() ->void {
  std::string mem{};
  get_album_new(mem);

  tab_detail_listbox = std::make_shared<Gtk::ListBox>();
  tab_detail_listbox->set_name("popalbum-list");
  // gtk_album_list.gtk_album_list_top = std::make_shared<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 20);
  gtk_album_list.gtk_album_list_1 = std::make_shared<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 20);
  gtk_album_list.gtk_album_list_2 = std::make_shared<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 20);

  gtk_album.gtk_album_box = std::make_shared<Gtk::Box>(Gtk::Orientation::VERTICAL, 15);
  gtk_album.gtk_album_name = std::make_shared<Gtk::Button>();
  gtk_album.gtk_album_name->set_can_shrink(true);

  set_pop_album_to_listbox(mem);

  tab_detail_listbox->append(*(gtk_album_list.gtk_album_list_1));
  tab_detail_listbox->append(*(gtk_album_list.gtk_album_list_2));

  tab_detail->append(*tab_detail_listbox);
}

new_gtk::new_gtk()
{
  set_title("ne-music");
  set_default_size(800, 600);

  main_box = std::make_shared<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 2);
  tab = std::make_shared<Gtk::Box>(Gtk::Orientation::VERTICAL, 0);
  tab->set_homogeneous(true);
  tab_detail = std::make_shared<Gtk::Box>(Gtk::Orientation::VERTICAL, 3);
  
  main_box->append(*tab);
  main_box->append(*tab_detail);

  recommend = std::make_shared<Gtk::Button>("推荐", false);
  recommend->signal_clicked().connect(sigc::mem_fun(*this, &new_gtk::recommend_clicked));
  discover = std::make_shared<Gtk::Button>("发现", false);
  home = std::make_shared<Gtk::Button>("主页", false);

  tab->append(*recommend);
  tab->append(*discover);
  tab->append(*home);

  set_child(*main_box);
}

// static void recommend_clicked(const GtkButton *button, gpointer box) {
//   (void)button;
//   std::string mem {};
//   get_album_new(mem);
//   set_pop_album_to_listbox(mem, GTK_WIDGET(box));
//   // get_pop_album((GtkListBox*)listbox);
// }


// void main_window(const GApplication *app) {
//   GtkWidget *window;
//   GtkWidget *window_box;
//   GtkWidget *tab;
//   GtkWidget *tab_detail;
//   GtkWidget *recommend;
//   GtkWidget *discover;
//   GtkWidget *home;

//   window = gtk_application_window_new(GTK_APPLICATION(app));
//   gtk_window_set_title(GTK_WINDOW(window), "new-music");
//   gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

//   window_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//   gtk_window_set_child(GTK_WINDOW(window), window_box);

//   tab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//   gtk_box_set_homogeneous(GTK_BOX(tab), TRUE);
//   gtk_box_append(GTK_BOX(window_box), tab);

//   recommend = gtk_button_new_with_label("推荐");
//   discover = gtk_button_new_with_label("发现");
//   home = gtk_button_new_with_label("主页");

//   tab_detail = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//   gtk_widget_set_hexpand(tab_detail, TRUE);
//   gtk_widget_set_vexpand(tab_detail, TRUE);
//   gtk_widget_set_halign(tab_detail, GTK_ALIGN_FILL);
//   gtk_box_append(GTK_BOX(window_box), tab_detail);

//   // list_box = gtk_grid_new();
//   // gtk_grid_set_column_homogeneous(GTK_GRID(list_box), TRUE);

//   gtk_box_append(GTK_BOX(tab), recommend);
//   gtk_box_append(GTK_BOX(tab), discover);
//   gtk_box_append(GTK_BOX(tab), home);

//   g_signal_connect(recommend, "clicked", G_CALLBACK(recommend_clicked),
//                    tab_detail);
//   gtk_window_present(GTK_WINDOW(window));
// }