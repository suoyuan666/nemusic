#include <memory>
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtkmm.h>
#include "gtkmm/button.h"
#include "gtkmm/listbox.h"
#include "gtkmm/image.h"
#endif

class new_gtk : public Gtk::Window {
 public:
  new_gtk();
  ~new_gtk() = default;

  auto recommend_clicked() -> void;
  auto set_pop_album_to_listbox(std::string& content) -> void;

 protected:
  std::shared_ptr<Gtk::Box> main_box;

  std::shared_ptr<Gtk::Box> tab;
  std::shared_ptr<Gtk::Box> tab_detail;

  std::shared_ptr<Gtk::Button> recommend;
  std::shared_ptr<Gtk::Button> discover;
  std::shared_ptr<Gtk::Button> home;

  std::shared_ptr<Gtk::ListBox> tab_detail_listbox;
  struct {
    // std::shared_ptr<Gtk::Box> gtk_album_list_top;
    std::shared_ptr<Gtk::Box> gtk_album_list_1;
    std::shared_ptr<Gtk::Box> gtk_album_list_2;
  } gtk_album_list;
  struct {
    std::shared_ptr<Gtk::Box> gtk_album_box;
    std::shared_ptr<Gtk::Image> gtk_album_image;
    std::shared_ptr<Gtk::Button> gtk_album_name;
  } gtk_album;
};
