#include <stddef.h>

struct mem_with_size {
  char *memory;
  size_t size;
};

void store_url_to_memory(char *url, struct mem_with_size *content);
