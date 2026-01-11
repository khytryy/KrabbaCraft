#pragma once

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <kc/debug/debug.h>
#include <toml/tomlc17.h>

#include <stdint.h>

#define TAR_MAX_MODS 32

typedef struct {
    int on_tick;
} tar_mod_t;

extern size_t mod_count;

extern const struct luaL_Reg tarLogger[];
extern lua_State *tarL;

extern tar_mod_t mods[TAR_MAX_MODS];

int luaopen_tarLogger(lua_State *L);

void tarInitLua();

void tarInit();

/*
    Prints a log with a log level info, for example:
    [NAME/INFO] Message
*/
static int tarLogInfo(lua_State *L);

/*
    Prints a log with a log level debug, for example:
    [NAME/DEBUG] Message
*/
static int tarLogDebug(lua_State *L);

/*
    Prints a log with a log level warning, for example:
    [NAME/WARNING] Message
*/
static int tarLogWarning(lua_State *L);
static int tarLogError(lua_State *L);
static int tarLogFerror(lua_State *L);

void tarOnTick(float time);