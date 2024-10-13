#ifndef CURL_UTILS_INCLUDE
#define CURL_UTILS_INCLUDE
#include "curl_utils/curl_utils.h"
#endif
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtk/gtk.h>
#endif

void set_pop_album_to_listbox(struct mem_with_size* content, GtkWidget *box);
void main_window(const GApplication *app);
