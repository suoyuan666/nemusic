#include "ne-gtk/window.h"
#include "css/tab.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <assert.h>
#ifndef GTK_INCLUDE
#define GTK_INCLUDE
#include <gtkmm.h>
#endif
#ifndef JSON_INCLUDE
#define JSON_INCLUDE
#include <nlohmann/json.hpp>
#endif

