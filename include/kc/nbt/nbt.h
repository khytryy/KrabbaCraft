#pragma once

#include <stdint.h>
#include <stddef.h>

#include <kc/debug/debug.h>
#include <assert.h>

#include <stdbool.h>
#include <string.h>

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef enum {
    NBT_TYPE_BYTE,
    NBT_TYPE_SHORT,
    NBT_TYPE_INT,
    NBT_TYPE_LONG,
    NBT_TYPE_FLOAT,
    NBT_TYPE_DOUBLE,
    NBT_TYPE_STRING,
    NBT_TYPE_LIST,
    NBT_TYPE_COMPOUND,
    NBT_TYPE_BYTE_ARRAY,
    NBT_TYPE_INT_ARRAY,
    NBT_TYPE_LONG_ARRAY,
    NBT_TYPE_FLOAT_ARRAY
} nbt_type_t;

typedef struct nbt_value_s nbt_value_t;

typedef struct nbt_list_s {
    nbt_type_t  type;
    size_t      size;
    size_t      capacity;

    nbt_value_t *elements;
} nbt_list_t;

typedef struct nbt_compound_s {
    size_t      size;
    size_t      capacity;

    nbt_value_t *elements;
} nbt_compound_t;

typedef struct nbt_value_s {
    nbt_type_t type;

    union {
        uint8_t         payload_byte;
        uint16_t        payload_short;
        int32_t         payload_int;
        uint64_t        payload_long;

        float           payload_float;
        double          payload_double;
        uint8_t         *payload_string;

        nbt_list_t      payload_list;
        nbt_compound_t  payload_compound;
    };
} nbt_value_s;

nbt_value_t nbtNewByte(uint8_t data);
nbt_value_t nbtNewShort(uint16_t data);
nbt_value_t nbtNewInt(int data);
nbt_value_t nbtNewLong(uint64_t data);
nbt_value_t nbtNewFloat(float data);
nbt_value_t nbtNewDouble(double data);
nbt_value_t nbtNewString(char *data);

// Lists

nbt_list_t *nbtNewList(nbt_type_t data_type);
void        nbtDeleteList(nbt_list_t *list);

void        nbtPushToList(nbt_list_t *list, nbt_value_t payload);
void        nbtPopFromList(nbt_list_t *list);

nbt_value_t nbtGetValueFromListAt(nbt_list_t *list, size_t index);
size_t      nbtGetListSize(nbt_list_t *list);

bool        nbtIsListEmpty(nbt_list_t *list);

// Compounds

nbt_compound_t *nbtNewCompound();
void            nbtDeleteCompound(nbt_compound_t *compound);

void        nbtPushToCompound(nbt_compound_t *compound, nbt_value_t payload);
void        nbtPopFromCompound(nbt_compound_t *compound);

nbt_value_t nbtGetValueFromCompoundAt(nbt_compound_t *compound, size_t index);
size_t      nbtGetCompoundSize(nbt_compound_t *compound);

bool        nbtIsCompoundEmpty(nbt_compound_t *compound);

typedef struct {
    uint8_t *data;
    size_t   size;
    size_t   capacity;
} nbt_buffer_t;

void nbtReserverBuffer(nbt_buffer_t *b, size_t s);
void nbtBufferWriteU8(nbt_buffer_t *b, uint8_t v);
void nbtBufferWriteU16(nbt_buffer_t *b, uint16_t v);
void nbtBufferWriteU32(nbt_buffer_t *b, uint32_t v);
void nbtBufferWriteU64(nbt_buffer_t *b, uint64_t v);
void nbtBufferWriteFloat(nbt_buffer_t *b, float f);
void nbtBufferWriteDouble(nbt_buffer_t *b, double d);
void nbtBufferWriteInt(nbt_buffer_t *b, int v);

void nbtSerializeValue(nbt_buffer_t *b, nbt_value_t *v);
void nbtSerializeList(nbt_buffer_t *b, nbt_list_t *list);
void nbtSerializeCompound(nbt_buffer_t *b, nbt_compound_t *c);