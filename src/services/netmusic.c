#include "services/netmusic.h"
#include "css/tab.h"
#include "gtk/gtk.h"

#include <curl/curl.h>
#include <curl/easy.h>
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtk/gtk.h>
#endif
#ifndef CJSON_INCLUDE
#define CJSON_INCLUDE
#include "cJSON/cJSON.h"
#endif

void get_album_new(struct mem_with_size *content) {
  store_url_to_memory("https://music.163.com/api/discovery/newAlbum", content);
  return;
}

void get_pop_album(GtkListBox *listbox) {
  struct mem_with_size content = {0, 0};
  get_album_new(&content);

  cJSON *json = cJSON_Parse(content.memory);
  if (json == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      fprintf(stderr, "Error before: %s\n", error_ptr);
    }
  } else {
    cJSON *album;
    cJSON *album_list = cJSON_GetObjectItemCaseSensitive(json, "albums");
    if (cJSON_IsArray(album_list)) {
      album = album_list->child;
      for (int i = 0; i < 2 && album != NULL; ++i) {
        GtkWidget *galbum_list = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
        gtk_box_set_homogeneous(GTK_BOX(galbum_list), TRUE);
        for (int j = 0; j < 5 && album != NULL; ++j) {
          cJSON *album_name = cJSON_GetObjectItemCaseSensitive(album, "name");
          cJSON *ablum_pic_url =
              cJSON_GetObjectItemCaseSensitive(album, "blurPicUrl");
          struct mem_with_size pix_buf = {0, 0};
          store_url_to_memory(ablum_pic_url->valuestring, &pix_buf);
          GError *err;
          GBytes *gpix_buf = g_bytes_new(pix_buf.memory, pix_buf.size);
          GdkTexture *texture = gdk_texture_new_from_bytes(gpix_buf, &err);

          if (err != NULL) {
            fprintf(stderr, "Unable to read file: %s\n", err->message);
            g_error_free(err);
            goto end;
          } else {
            GtkWidget *gpicture =
                gtk_image_new_from_paintable(GDK_PAINTABLE(texture));
            GtkWidget *glabel = gtk_button_new_with_label(album_name->valuestring);

            GtkWidget *galbum = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
            gtk_box_append(GTK_BOX(galbum), gpicture);
            gtk_box_append(GTK_BOX(galbum), glabel);
            gtk_widget_set_name(gpicture, "album-picture");
            gtk_widget_set_name(galbum, "album");
            gtk_widget_set_name(glabel, "album-name");

            GtkCssProvider *provider = gtk_css_provider_new();
            gtk_css_provider_load_from_string(provider, tab_css);
            GdkDisplay *display = gdk_display_get_default();
            gtk_style_context_add_provider_for_display(
                display, GTK_STYLE_PROVIDER(provider),
                GTK_STYLE_PROVIDER_PRIORITY_USER);

            gtk_box_append(GTK_BOX(galbum_list), galbum);
          }
          album = album->next;
        }
        gtk_list_box_append(GTK_LIST_BOX(listbox), galbum_list);
      }
    } else {
      perror("recommend_clicked: type of album_list != Arrary\n");
    }
  }

end:
  cJSON_Delete(json);
  free(content.memory);
  return;
}
