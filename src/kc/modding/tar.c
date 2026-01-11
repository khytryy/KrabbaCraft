#include <kc/modding/tar.h>

tar_mod_t mods[TAR_MAX_MODS];
size_t mod_count = 0;

const struct luaL_Reg tarLogger[] = {
    { "info", tarLogInfo },
    { "debug", tarLogDebug },
    { "warn", tarLogWarning },
    { "error", tarLogError },
    { "fatal", tarLogFerror },
    { NULL, NULL }
};

lua_State *tarL;

int luaopen_tarLogger(lua_State *L) {
    luaL_newlib(L, tarLogger);
    return 1;
}

void tarInitLua() {
    tarL = luaL_newstate();
    luaL_openlibs(tarL);

    // Load tar libraries
    luaL_requiref(tarL, "tarLogger", luaopen_tarLogger, 1);
    lua_pop(tarL, 1);
}

void tarInit() {
    tarInitLua();

    if (!tarL) {
        dbgWrite("TAR", LOG_LEVEL_FATAL_ERROR, "Lua state not initialized!\n");
        return;
    }

    toml_result_t result = toml_parse_file_ex(".krabbacraft/mods/manifest.toml");
    if (!result.ok) {
        dbgWrite("TOML", LOG_LEVEL_ERROR, result.errmsg, "\n");
        return;
    }

    // Check if tar.mods.files is an array
    toml_datum_t tar_mods = toml_seek(result.toptab, "tar.mods.files");
    if (tar_mods.type != TOML_ARRAY) {
        dbgWrite("TAR", LOG_LEVEL_ERROR, "tar.mods.files is not an array!\n");
        toml_free(result);
        return;
    }

    dbgWrite("TAR", LOG_LEVEL_INFO, "Starting up tar mods...\n");

    for (size_t i = 0; i < tar_mods.u.arr.size; i++) {
        toml_datum_t lua_file = tar_mods.u.arr.elem[i];

        if (lua_file.type != TOML_STRING) {
            dbgWrite("TAR", LOG_LEVEL_ERROR,
                     "tar.mods.files element is not a string\n");
            continue;
        }

        const char *filename = lua_file.u.s;
        if (!filename) {
            dbgWrite("TAR", LOG_LEVEL_ERROR,
                     "Lua mod path is NULL\n");
            continue;
        }

        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath),
                 ".krabbacraft/mods/%s", filename);

        if (luaL_loadfile(tarL, fullpath) != LUA_OK) {
            dbgWrite("LUA", LOG_LEVEL_ERROR,
                     lua_tostring(tarL, -1), "\n");
            lua_pop(tarL, 1);
            continue;
        }

        dbgWrite("TAR", LOG_LEVEL_INFO, "Loaded: %s\n", fullpath);

        // Run the mod and expect it to return a table
        if (lua_pcall(tarL, 0, 1, 0) != LUA_OK) {
            dbgWrite("LUA", LOG_LEVEL_ERROR,
                     lua_tostring(tarL, -1), "\n");
            lua_pop(tarL, 1);
        }

        if (lua_istable(tarL, -1)) {
            lua_getfield(tarL, -1, "tarOnTick");
            if (lua_isfunction(tarL, -1)) {
                if (mod_count < TAR_MAX_MODS) {
                    mods[mod_count].on_tick = luaL_ref(tarL, LUA_REGISTRYINDEX);
                    mod_count++;
                }
                else {
                    lua_pop(tarL, 1);
                }
            } else {
                lua_pop(tarL, 1);
            }
        }

        lua_pop(tarL, 1);
    }

    toml_free(result);
}


static int tarLogInfo(lua_State *L) {
    const char *mod = luaL_checkstring(L, 1);
    const char *msg = luaL_checkstring(L, 2);

    dbgWrite(mod, LOG_LEVEL_INFO, "%s\n", msg);

    return 0;
}

static int tarLogDebug(lua_State *L) {
    const char *mod = luaL_checkstring(L, 1);
    const char *msg = luaL_checkstring(L, 2);
    
    dbgWrite(mod, LOG_LEVEL_DEBUG, "%s\n", msg);

    return 0;
}

static int tarLogWarning(lua_State *L) {
    const char *mod = luaL_checkstring(L, 1);
    const char *msg = luaL_checkstring(L, 2);
    
    dbgWrite(mod, LOG_LEVEL_WARNING, "%s\n", msg);
    
    return 0;
}

static int tarLogError(lua_State *L) {
    const char *mod = luaL_checkstring(L, 1);
    const char *msg = luaL_checkstring(L, 2);
    
    dbgWrite(mod, LOG_LEVEL_ERROR, "%s\n", msg);
    
    return 0;
}

static int tarLogFerror(lua_State *L) {
    const char *mod = luaL_checkstring(L, 1);
    const char *msg = luaL_checkstring(L, 2);
    
    dbgWrite(mod, LOG_LEVEL_FATAL_ERROR, "%s\n", msg);
    
    return 0;
}

void tarOnTick(float time) {
    for (size_t i = 0; i < mod_count; i++) {
        lua_rawgeti(tarL, LUA_REGISTRYINDEX, mods[i].on_tick);
        lua_pushnumber(tarL, time);

        if (lua_pcall(tarL, 1, 0, 0) != LUA_OK) {
            dbgWrite("LUA", LOG_LEVEL_ERROR, "%s\n", lua_tostring(tarL, -1));
            lua_pop(tarL, 1);
        }
    }
}