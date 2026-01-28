#include <kc/nbt/nbt.h>

nbt_value_t nbtNewByte(uint8_t data) {
    nbt_value_t value;

    value.type = NBT_TYPE_BYTE;
    value.payload_byte = data;

    return value;
}

nbt_value_t nbtNewShort(uint16_t data) {
    nbt_value_t value;

    value.type = NBT_TYPE_SHORT;
    value.payload_short = data;

    return value;
}

nbt_value_t nbtNewInt(int data) {
    nbt_value_t value;

    value.type = NBT_TYPE_INT;
    value.payload_int = data;

    return value;
}

nbt_value_t nbtNewLong(uint64_t data) {
    nbt_value_t value;

    value.type = NBT_TYPE_LONG;
    value.payload_long = data;

    return value;
}

nbt_value_t nbtNewFloat(float data) {
    nbt_value_t value;

    value.type = NBT_TYPE_FLOAT;
    value.payload_float = data;

    return value;
}

nbt_value_t nbtNewDouble(double data) {
    nbt_value_t value;

    value.type = NBT_TYPE_DOUBLE;
    value.payload_double = data;

    return value;
}

nbt_value_t nbtNewString(char *data) {
    nbt_value_t value;

    value.type = NBT_TYPE_STRING;
    value.payload_string = (uint8_t *)data;

    return value;
}

// Lists
nbt_list_t *nbtNewList(nbt_type_t data_type) {
    nbt_list_t *list = (nbt_list_t *)malloc(sizeof(nbt_list_t));
    if (list == NULL) {
        dbgPerror("NBT", "Failed to allocate memory for a list!");
        abort();
    }

    list->type = data_type;
    list->elements = NULL;

    list->size = 0;
    list->capacity = 0;

    return list;
}

void nbtDeleteList(nbt_list_t *list) {
    free(list->elements);

    list->capacity = 0;
    list->size = 0;
}

void nbtPushToList(nbt_list_t *list, nbt_value_t payload) {
    // If the list is empty, allocate memory for one element
    if (list->elements == NULL) {
        list->elements = (nbt_value_t *)malloc(sizeof(nbt_value_t));
        list->capacity = 1;
    }
    // If the size is more or the same as the capacity, oouble the capacity and reallocate memory for elements
    else if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->elements = (nbt_value_t *)realloc(list->elements, list->capacity * sizeof(nbt_value_t));
    }

    list->elements[list->size] = payload;
    list->size++;
}

void nbtPopFromList(nbt_list_t *list) {
    if (list->size > 0) {
        list->size--;
    }
}

nbt_value_t nbtGetValueFromListAt(nbt_list_t *list, size_t index) {
    if (index > list->size) {
        dbgWrite("NBT", LOG_LEVEL_FATAL_ERROR, "Index is out of bounds!\n");
        abort();
    }

    return list->elements[index];
}

size_t nbtGetListSize(nbt_list_t *list) {
    return list->size;
}

bool nbtIsListEmpty(nbt_list_t *list) {
    return list->size == 0 ? true : false;
}

// Compounds
nbt_compound_t *nbtNewCompound() {
    nbt_compound_t *compound = (nbt_compound_t *)malloc(sizeof(nbt_compound_t));
    if (compound == NULL) {
        dbgPerror("NBT", "Failed to allocate memory for a compound!");
        abort();
    }

    compound->size      = 0;
    compound->capacity  = 0;

    compound->elements  = NULL;
}

void nbtDeleteCompound(nbt_compound_t *compound) {
    free(compound->elements);

    compound->capacity = 0;
    compound->size = 0;
}

void nbtPushToCompound(nbt_compound_t *compound, nbt_value_t payload) {
    // If the list is empty, allocate memory for one element
    if (compound->elements == NULL) {
        compound->elements = (nbt_value_t *)malloc(sizeof(nbt_value_t));
        compound->capacity = 1;
    }
    // If the size is more or the same as the capacity, oouble the capacity and reallocate memory for elements
    else if (compound->size >= compound->capacity) {
        compound->capacity *= 2;
        compound->elements = (nbt_value_t *)realloc(compound->elements, compound->capacity * sizeof(nbt_value_t));
    }

    compound->elements[compound->size] = payload;
    compound->size++;
}

void nbtPopFromCompound(nbt_compound_t *compound) {
    if (compound->size > 0) {
        compound->size--;
    }
}

nbt_value_t nbtGetValueFromCompoundAt(nbt_compound_t *compound, size_t index) {
    if (index > compound->size) {
        dbgWrite("NBT", LOG_LEVEL_FATAL_ERROR, "Index is out of bounds!\n");
        abort();
    }

    return compound->elements[index];
}

size_t nbtGetCompoundSize(nbt_compound_t *compound) {
    return compound->size;
}

bool nbtIsCompoundEmpty(nbt_compound_t *compound) {
    return compound->size == 0 ? true : false;
}

void nbtReserverBuffer(nbt_buffer_t *b, size_t s) {
    if (b->size + s > b->capacity) {
        size_t new_capacity = b->capacity ? b->capacity * 2 : 64;
        while (new_capacity < b->size + s) {
            new_capacity *= 2;
        }
        b->data = (uint8_t *)realloc(b->data, new_capacity);
        if (!b->data) {
            dbgWrite("NBT", LOG_LEVEL_FATAL_ERROR, "Failed to allocate memory for a buffer!\n");
            abort();
        }
        b->capacity = new_capacity;
    }
}

void nbtBufferWriteU8(nbt_buffer_t *b, uint8_t v) {
    nbtReserverBuffer(b, 1);
    b->data[b->size++] = v;
}

void nbtBufferWriteU16(nbt_buffer_t *b, uint16_t v) {
    nbtReserverBuffer(b, 2);
    v = htons(v);
    memcpy(b->data + b->size, &v, 2);
    b->size += 2;
}

void nbtBufferWriteU32(nbt_buffer_t *b, uint32_t v) {
    nbtReserverBuffer(b, 4);
    v = htonl(v);
    memcpy(b->data + b->size, &v, 4);
    b->size += 4;
}

void nbtBufferWriteU64(nbt_buffer_t *b, uint64_t v) {
    uint32_t hi = htonl((uint32_t)(v >> 32));
    uint32_t lo = htonl((uint32_t)(v & 0xFFFFFFFF));
    nbtBufferWriteU32(b, hi);
    nbtBufferWriteU32(b, lo);
}

void nbtBufferWriteFloat(nbt_buffer_t *b, float f) {
    uint32_t tmp;
    memcpy(&tmp, &f, 4);
    nbtBufferWriteU32(b, tmp);
}

void nbtBufferWriteDouble(nbt_buffer_t *b, double d) {
    uint64_t tmp;
    memcpy(&tmp, &d, 8);
    nbtBufferWriteU64(b, tmp);
}

void nbtBufferWriteInt(nbt_buffer_t *b, int32_t v) {
    nbtBufferWriteU32(b, (uint32_t)v);
}