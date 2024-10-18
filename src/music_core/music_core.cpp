#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vlc/vlc.h>

libvlc_instance_t *instance = NULL;
libvlc_media_player_t *media_player = NULL;
libvlc_media_t *media = NULL;

int play_music_from_url(char *url, int64_t *total_time) {
  instance = libvlc_new(0, NULL);
  if (!instance) {
    fprintf(stderr, "Failed to create VLC instance\n");
    return 1;
  }

  if (media_player != NULL) {
    libvlc_media_release(media);
    libvlc_media_player_stop(media_player);
    libvlc_media_player_release(media_player);
  }

  media_player = libvlc_media_player_new(instance);
  if (!media_player) {
    fprintf(stderr, "Failed to create media player\n");
    libvlc_release(instance);
    return 1;
  }

  media = libvlc_media_new_location(instance, url);
  if (!media) {
    fprintf(stderr, "Failed to create media\n");
    libvlc_media_player_release(media_player);
    libvlc_release(instance);
    return 1;
  }

  libvlc_media_player_set_media(media_player, media);
  *total_time = libvlc_media_player_get_length(media_player);
  libvlc_media_player_play(media_player);
  
  while (libvlc_media_player_is_playing(media_player));

  libvlc_media_release(media);
  libvlc_media_player_stop(media_player);
  libvlc_media_player_release(media_player);

  return 0;
}