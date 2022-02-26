#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)


extern "C" {
    void WebFilestorage_save(const char* key, const char* file);
    const char* WebFilestorage_load(const char* key);
    void WebFilestorage_remove(const char* key);
}


#endif
