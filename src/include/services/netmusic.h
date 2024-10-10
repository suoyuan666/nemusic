#include "curl_utils/curl_utils.h"
#include <stddef.h>
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtk/gtk.h>
#endif

enum AREA {
    ZH,
    EA,
    KR,
    JP,
    ALL
};

void get_album_new(struct mem_with_size *content);
void get_pop_album(GtkListBox *listbox);
