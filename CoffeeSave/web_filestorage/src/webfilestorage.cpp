#define EXTENSION_NAME web_filestorage
#define LIB_NAME "web_filestorage"
#define MODULE_NAME "web_filestorage"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>
#include <dmsdk/dlib/log.h>
#include "luautils.h"
#include "webfilestorage.h"

#if defined(DM_PLATFORM_HTML5)

static int SaveFile(lua_State* L)
{
	int top = lua_gettop(L);

	const char* key = luaL_checkstring(L, 1);
	const char* file = luaL_checkstring(L, 2);

    WebFilestorage_save(key, file);

	assert(top == lua_gettop(L));
	return 0;
}

static int LoadFile(lua_State* L)
{
	int top = lua_gettop(L);

	const char* key = luaL_checkstring(L, 1);

    const char* result = WebFilestorage_load(key);
	int len = strlen(result);

	//dmLogError("load result %s %d", result, len);
  	if (result == 0 || strcmp(result, "") == 0) {
        lua_pushnil(L);
    } else {
        lua_pushlstring(L, result, len);
    }

	assert(top + 1 == lua_gettop(L));
	return 1;
}

static int RemoveFile(lua_State* L)
{
	int top = lua_gettop(L);

	const char* key = luaL_checkstring(L, 1);

    WebFilestorage_remove(key);

	assert(top == lua_gettop(L));
	return 0;
}

static const luaL_reg Module_methods[] =
{
    {"save_file", SaveFile},
    {"load_file", LoadFile},
    {"remove_file", RemoveFile},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}
#endif

dmExtension::Result AppInitializewebfilestorageExtension(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializewebfilestorageExtension(dmExtension::Params* params) {
	#if defined(DM_PLATFORM_HTML5)
		LuaInit(params->m_L);
	#else
		printf("Extension %s is not supported\n", MODULE_NAME);
	#endif
	return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizewebfilestorageExtension(dmExtension::AppParams* params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizewebfilestorageExtension(dmExtension::Params* params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result UpdatewebfilestorageExtension(dmExtension::Params* params) {
	return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(web_filestorage, LIB_NAME, AppInitializewebfilestorageExtension, AppFinalizewebfilestorageExtension, InitializewebfilestorageExtension, UpdatewebfilestorageExtension, 0, FinalizewebfilestorageExtension)