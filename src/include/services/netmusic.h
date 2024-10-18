#ifndef CURL_UTILS_INCLUDE
#define CURL_UTILS_INCLUDE
#include "asio_utils/asio_utils.h"
#endif
#ifndef GLIB_USTRING
#define GLIB_USTRING
#include <glibmm/ustring.h>
#endif
#include <stddef.h>

enum AREA {
    ZH,
    EA,
    KR,
    JP,
    ALL
};

void get_album_new(std::string &content);
void get_album_list(char *id, std::string &content);
void get_song_url(char *id, std::string &content);
