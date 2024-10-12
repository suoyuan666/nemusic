#include "services/netmusic.h"
#include <string.h>

void get_album_new(struct mem_with_size *content) {
  store_url_to_memory("https://music.163.com/api/discovery/newAlbum", content);
}

void get_album_list(char *id, struct mem_with_size *content) {
  char url[64] = "https://music.163.com/api/v1/album/";
  strcat(url, id);
  store_url_to_memory(url, content);
}