#include "services/netmusic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_album_new(struct mem_with_size *content) {
  store_url_to_memory("https://music.163.com/api/discovery/newAlbum", content);
}

void get_album_list(char *id, struct mem_with_size *content) {
  char url[64] = "https://music.163.com/api/v1/album/";
  strcat(url, id);
  store_url_to_memory(url, content);
}

/*
* level:
*   standard: 标准
*   higher: 较高
*   exhigh: 极高
*   lossless: 无损
*   hires: Hi-Res
*   jyeffect: 高清环绕声
*   sky: 沉浸环绕声
*   dolby: 杜比全景声
*   jymaster: 超清母带
*   杜比全景声音质需要设备支持，不同的设备可能会返回不同码率的 url。cookie 需要传入 `os=pc` 保证返回正常码率的 url。
*/

void get_song_url(char *id, struct mem_with_size *content) {
  char url[128] = "https://music.163.com/api/song/enhance/player/url/v1?ids=[";
  strcat(url, id);
  strcat(url, "]&level=standard&encodeType=flac");
  printf("url : %s\n", url);
  store_url_to_memory(url, content);
}