#include "ne-gtk/window.h"
#include "services/netmusic.h"
#include "music_core/music_core.h"
#include "css/tab.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <assert.h>
#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtkmm.h>
#endif
#ifndef JSON_INCLUDE
#define JSON_INCLUDE
#include <nlohmann/json.hpp>
#endif
std::array<int, 512> album_ids {};
std::array<unsigned int, 512> song_ids {};

int album_index = 0;
int song_index = 0;

GtkWidget *listbox_to_del = NULL;

void uint2str(unsigned int integer, char *str, bool spearte) {
  unsigned int bak = integer;
  int len = 1;
  for (unsigned int tmp = integer; (tmp /= 10) != 0; ++len);
  if (spearte) {
    str[len] = ':';
  }
  for (; (integer /= 10) != 0 || len > 0; --len) {
    str[len - 1] = '0' + bak - integer * 10;
    bak = integer;
  }
}

void int2str(int integer, char *str, bool spearte) {
  int bak = integer;
  int len = 1;
  for (int tmp = integer; (tmp /= 10) != 0; ++len);
  if (spearte) {
    str[len] = ':';
  }
  for (; (integer /= 10) != 0 || len > 0; --len) {
    str[len - 1] = '0' + bak - integer * 10;
    bak = integer;
  }
}

// void play_song(const GtkButton *button, gpointer box) {
//   char id[16] = {0};
//   const char *name = gtk_button_get_label(GTK_BUTTON(button));
//   for (size_t i = 0; i < sizeof(id); ++i) {
//     if (name[i] == ':') {
//       break;
//     }
//     id[i] = name[i];
//   }
//   std::string buf {};
//   int song_index = atoi(id) - 1;

//   assert(song_index >= 0);

//   char sid[32] = {0};
//   uint2str(song_ids[song_index], sid, 0);
//   get_song_url(sid, buf);
  
//   cJSON *json = cJSON_Parse(buf.c_str());
//   if (json == NULL) {
//     const char *error_ptr = cJSON_GetErrorPtr();
//     if (error_ptr != NULL) {
//       fprintf(stderr, "Error before: %s\n", error_ptr);
//     }
//   } else {
//     cJSON *song_list = cJSON_GetObjectItemCaseSensitive(json, "data");
//     if (!cJSON_IsArray(song_list)) {
//       fprintf(stderr, "type of song_list != Arrary");
//     } else {
//       cJSON *song = NULL;
//       cJSON_ArrayForEach(song, song_list) {
//         cJSON *url = cJSON_GetObjectItemCaseSensitive(song, "url");
//         printf("url: %s\n", url->valuestring);
//         exit(0);
//         (void)box;
//         // int64_t time = 0;
//         // // play_music_from_url(url->valuestring, &time);
//         // GtkWidget *progress_bar = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, time, 10);
//         // gtk_box_append(GTK_BOX(box), progress_bar);
//       }
//     }
//   }
// }

// auto set_album_list(const GtkButton *button, gpointer ptr) -> void {
//   char id[16] = {0};
//   const char *name = gtk_button_get_label(GTK_BUTTON(button));
//   for (size_t i = 0; i < sizeof(id); ++i) {
//     if (name[i] == ':') {
//       break;
//     }
//     id[i] = name[i];
//   }
//   std::string buf {};

//   char cid[32] = {};
//   int album_index = atoi(id) - 1;

//   assert(album_index >= 0);

//   int2str(album_ids[album_index], cid, 0);

//   get_album_list(cid, buf);

//   cJSON *json = cJSON_Parse(buf.c_str());
//   if (json == NULL) {
//     const char *error_ptr = cJSON_GetErrorPtr();
//     if (error_ptr != NULL) {
//       fprintf(stderr, "Error before: %s\n", error_ptr);
//     }
//   } else {
//     cJSON *song_list = cJSON_GetObjectItemCaseSensitive(json, "songs");
//     if (!cJSON_IsArray(song_list)) {
//       fprintf(stderr, "type of song_list != Arrary");
//     } else {
//       cJSON *song = NULL;
//       GtkWidget *box = gtk_list_box_new();
//       if (listbox_to_del != NULL) {
//         gtk_box_remove(GTK_BOX(ptr), listbox_to_del);
//       }
//       gtk_box_append(GTK_BOX(ptr), box);
//       cJSON_ArrayForEach(song, song_list) {
//         cJSON *song_name = cJSON_GetObjectItemCaseSensitive(song, "name");
//         cJSON *song_id = cJSON_GetObjectItemCaseSensitive(song, "id");
//         unsigned int a = song_id->valuedouble;
//         song_ids[song_index] = a;
//         song_index += 1;

//         char name[128] = {};
//         int2str(song_index, (char *)name, 1);
//         strcat(name, song_name->valuestring);
//         GtkWidget *g_song_label =
//             gtk_button_new_with_label(name);
//         gtk_list_box_append(GTK_LIST_BOX(box), g_song_label);
//         g_signal_connect(g_song_label, "clicked", G_CALLBACK(play_song), ptr);
//       }
//     }
//   }
// }

auto new_gtk::set_pop_album_to_listbox(std::string& content) -> void {

  std::cout << content << std::endl;
  
  exit(0);

  nlohmann::json json = nlohmann::json::parse(content.data());
  // cJSON *json = cJSON_Parse(content.c_str());
  if (json == NULL) {
      fprintf(stderr, "Error before\n");
  } else {
    // cJSON *album;
    // cJSON *album_list = cJSON_GetObjectItemCaseSensitive(json, "albums");

    const auto album_list = json.at("albums");
 
    if (album_list.is_array()) {
      auto album = album_list.begin();
      for (int i = 0; i < 2 && album != album_list.end(); ++i) {
        // GtkWidget *galbum_list = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
        for (int j = 0; j < 5 && album != album_list.end(); ++j) {

          // cJSON *album_id = cJSON_GetObjectItemCaseSensitive(album, "id");
          album_ids[album_index] = album->at("id");
          album_index++;

          // cJSON *album_name = cJSON_GetObjectItemCaseSensitive(album, "name");
          // cJSON *ablum_pic_url =
          //     cJSON_GetObjectItemCaseSensitive(album, "blurPicUrl");
          std::string pix_buf {};
          std::string str = album->at("blurPicUrl");
          store_url_to_memory(str, pix_buf);
          // GError *err = NULL;
          std::shared_ptr<Glib::Bytes> gpix_buf = Glib::Bytes::create(pix_buf.data(), pix_buf.size());
          // GBytes *gpix_buf = g_bytes_new(pix_buf.c_str(), pix_buf.size());
          GError *err = NULL;
          std::shared_ptr<Gdk::Texture> gpix_texture = Gdk::Texture::create_from_bytes(gpix_buf);
          // GdkTexture *texture = gdk_texture_new_from_bytes(gpix_buf, &err);

          if (err != NULL) {
            fprintf(stderr, "Unable to read file: %s\n", err->message);
            g_error_free(err);
          } else {
            gtk_album.gtk_album_image = std::make_shared<Gtk::Image>(gpix_texture);
            // GtkWidget *gpicture =
            //     gtk_image_new_from_paintable(GDK_PAINTABLE(texture));
            std::string name = album->at("name");
            name.append(":");
            // char name[128] = {};
            // int2str(album_index, (char*)name, 1);
            // strcat(name, album_name->valuestring);

            

            // GtkWidget *glabel = gtk_button_new_with_label(name);
            gtk_album.gtk_album_name->set_label(name);
            

            // g_signal_connect(glabel, "clicked", G_CALLBACK(set_album_list), box);
            // gtk_image_set_pixel_size(GTK_IMAGE(gpicture), 100);
            // gtk_widget_set_vexpand(gpicture, TRUE);
            // gtk_widget_set_hexpand(gpicture, TRUE);
            // gtk_widget_set_halign(gpicture, GTK_ALIGN_FILL);

            // gtk_button_set_can_shrink(GTK_BUTTON(glabel), TRUE);

            gtk_album.gtk_album_box->append(*(gtk_album.gtk_album_image));
            gtk_album.gtk_album_box->append(*(gtk_album.gtk_album_name));

            gtk_album.gtk_album_image->set_name("album-picture");
            gtk_album.gtk_album_name->set_name("album-name");
            gtk_album.gtk_album_image->set_name("album-picture");

            // gtk_widget_set_name(gpicture, "album-picture");
            // gtk_widget_set_name(galbum, "album");
            // gtk_widget_set_name(glabel, "album-name");
            // gtk_widget_set_name(GTK_WIDGET(list_box), "listbox");

            // GtkCssProvider *provider = gtk_css_provider_new();
            // gtk_css_provider_load_from_string(provider, tab_css.data());
            // GdkDisplay *display = gdk_display_get_default();
            // gtk_style_context_add_provider_for_display(
            //     display, GTK_STYLE_PROVIDER(provider),
            //     GTK_STYLE_PROVIDER_PRIORITY_USER);

            // gtk_box_append(GTK_BOX(galbum_list), galbum);
          }
          ++album;
        }
      }
    } else {
      perror("recommend_clicked: type of album_list != Arrary\n");
    }
  }

  return;
}