#include <stdbool.h>
#include <stdio.h>

#include "services/netmusic.h"
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtk/gtk.h>
#endif
// #ifndef CJSON_INCLUDE
// #define CJSON_INCLUDE
// #include "cJSON/cJSON.h"
// #endif

static void recommend_clicked(const GtkButton *button, gpointer listbox) {
  (void)button;
//   struct mem_with_size content = {0, 0};
//   get_album_new(&content);

//   cJSON *json = cJSON_Parse(content.memory);
//   if (json == NULL) {
//     const char *error_ptr = cJSON_GetErrorPtr();
//     if (error_ptr != NULL) {
//       fprintf(stderr, "Error before: %s\n", error_ptr);
//     }
//   } else {
//     cJSON *album;
//     cJSON *album_list = cJSON_GetObjectItemCaseSensitive(json, "albums");
//     if (cJSON_IsArray(album_list)) {
//       album = album_list->child;
//       // int width = 1;
//       // int height = 1;
//       for (int i = 0; i < 2 && album != NULL; ++i) {
//         GtkWidget *galbum_list = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
//         gtk_box_set_homogeneous(GTK_BOX(galbum_list), TRUE);
//         for (int j = 0; j < 5 && album != NULL; ++j) {
//           cJSON *album_name = cJSON_GetObjectItemCaseSensitive(album, "name");
//           cJSON *ablum_pic_url =
//               cJSON_GetObjectItemCaseSensitive(album, "blurPicUrl");
//           struct mem_with_size pix_buf = {0, 0};
//           store_url_to_memory(ablum_pic_url->valuestring, &pix_buf);
//           GError *err;
//           GBytes *gpix_buf = g_bytes_new(pix_buf.memory, pix_buf.size);
//           GdkTexture *texture = gdk_texture_new_from_bytes(gpix_buf, &err);

//           if (err != NULL) {
//             fprintf(stderr, "Unable to read file: %s\n", err->message);
//             g_error_free(err);
//             goto end;
//           } else {
//             GtkWidget *gpicture =
//                 gtk_image_new_from_paintable(GDK_PAINTABLE(texture));
//             GtkWidget *glabel = gtk_label_new(album_name->valuestring);

//             GtkWidget *galbum = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
//             gtk_box_append(GTK_BOX(galbum), gpicture);
//             gtk_box_append(GTK_BOX(galbum), glabel);
//             gtk_widget_set_name(gpicture, "album-picture");
//             gtk_widget_set_name(galbum, "album");

//             GtkCssProvider *provider = gtk_css_provider_new();
//             gtk_css_provider_load_from_string(provider, tab_css);
//             GdkDisplay *display = gdk_display_get_default();
//             gtk_style_context_add_provider_for_display(
//                 display, GTK_STYLE_PROVIDER(provider),
//                 GTK_STYLE_PROVIDER_PRIORITY_USER);

//             gtk_box_append(GTK_BOX(galbum_list), galbum);
//             // gtk_grid_attach(GTK_GRID(listbox), galbum, width, height, 1, 1);
//             // if (++width > 5) {
//             //   height += 1;
//             //   width = 1;
//             // }
//             g_print("a\n");
//           }
//           album = album->next;
//         }
//         gtk_list_box_append(GTK_LIST_BOX((GtkListBox*) listbox), galbum_list);
//       }
//     } else {
//       perror("recommend_clicked: type of album_list != Arrary\n");
//     }
//   }

// end:
//   cJSON_Delete(json);
//   free(content.memory);
//   return;
  get_pop_album((GtkListBox*)listbox);
}

static void main_window(const GApplication *app) {
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
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

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

int main(int argc, char *argv[]) {
  GtkApplication *app;
  int stat;

  app = gtk_application_new("com.suoyuan.newmusic", G_APPLICATION_HANDLES_OPEN);
  g_signal_connect(app, "activate", G_CALLBACK(main_window), NULL);
  stat = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return stat;
}
