#include "asio_utils/asio_utils.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

constexpr std::string_view user_agent =
    "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) "
    "Chrome/129.0.0.0 Safari/537.36";

static size_t write2mem(void *contents, size_t size, size_t nmemb,
                                  void *userp) {
  // std::string *mem = (std::string *)userp;

  static_cast<std::string*>(userp)->append(static_cast<char*>(contents));
  // char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  // if (!ptr) {
  //   /* out of memory! */
  //   perror("write2mem: not enough memory (realloc returned NULL)\n");
  //   return 0;
  // }

  // mem->memory = ptr;
  // memcpy(&(mem->memory[mem->size]), contents, realsize);
  // mem->size += realsize;
  // mem->memory[mem->size] = 0;

  return size * nmemb;
}

void store_url_to_memory(std::string_view url, std::string &content) {
  CURL *curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.data());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write2mem);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent.data());

    CURLcode rs = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (rs != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(rs));
      return;
    }
  }
  return;
}
