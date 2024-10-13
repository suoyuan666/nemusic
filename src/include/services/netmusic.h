#ifndef CURL_UTILS_INCLUDE
#define CURL_UTILS_INCLUDE
#include "curl_utils/curl_utils.h"
#endif
#include <stddef.h>

enum AREA {
    ZH,
    EA,
    KR,
    JP,
    ALL
};

void get_album_new(struct mem_with_size *content);
void get_album_list(char *id, struct mem_with_size *content);
void get_song_url(char *id, struct mem_with_size *content);
