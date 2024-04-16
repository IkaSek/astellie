/// types.h
/// This file is a part of the astellie.
/// this file provides basic types expected by a minecraft client, ie VarInts and Vectors.

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define VARINT_MAX 5
#define VARLONG_MAX 10

#define Vector(t) \
  struct { \
    t *vec_data; \
    size_t vec_length; \
    size_t vec_size; \
  }
#define vectorFuncs(t) \
  Vector(t) *vec_##t##Init() { \
    Vector(t) *vec = malloc(sizeof Vector_##t); \
    vec->vec_data = malloc(sizeof(t)*32); \
    vec->vec_length = 32; \
    vec->vec_size = 0; \
    return vec; \
  } \
  void vec_##t##AppendSingle(Vector(t) *vec, t data) { \
    if(++vec->vec_size == vec->vec_length) { \
      vec->vec_length += 32 \
      vec->vec_data = realloc(vec->vec_data, vec->vec_length*sizeof(t)); \
    } \
    vec->vec_data[vec->vec_size] = t;\
  } \
  void vec_##t##AppendSlice(Vector(t) *vec, t data[]) { \
    for(size_t i = 0; i < sizeof(data)/sizeof(t); ++i) { \
      vec_##t##AppendSingle(vec, t[i]); \
    } \
  } \
  void vec_##t##CutSingle(Vector(t) *vec) { \
    if(--vec->vec_size % 32 == 0) { \
      vec->vec_length -= 32; \
      vec->vec_data = realloc(vec->vec_data, vec->vec_length*sizeof(t)); \
    } \
  } \
  void vec_##t##CutN(Vector(t) *vec, size_t n) { \
    for(size_t m = n; m > 0; --m){ \
      vec_##t##CutSingle(vec);\
    } \
  } \
  void vec_##t##Free(Vector(t) *vec) { \
    free(vec->vec_data); \
    free(vec); \
  }

#ifndef _optional_error_handler
//! the type of the optional
//! message, the message
#define _optional_error_handler(type, message) fprintf(stderr, "Optional(%s): %s", message);
#endif
#define Optional(t) \
  struct { \
    t *data; \
    bool is_set; \
  } 
#define optionalFuncs(t) \
  Optional(t) *opt_##t##Init() { \
    Optional(t) *opt = malloc(Optional_##t); \
    opt->data = malloc(sizeof(##t##)); \
    opt->is_set = false; \
    return opt; \
  } \
  void opt_##t##Set(Optional_##t *opt, t data) { \
    opt->data = data; \
    opt->is_set = true; \
  } \
  t opt_##t##Get(Optional_##t *opt) { \
    if(opt->is_set == true) return opt->data; \
    else _optional_error_handler(t, "optional is null."); \
  } \
  void opt_##t##Destroy(Optional_##t *opt) { \
    free(opt->data); \
    free(opt); \
  }

typedef enum {
  none,
  tried_to_remove_too_much,
} StringError;

typedef struct {
  char *char_vec;
  size_t char_vec_size;
  size_t char_vec_capacity;
} String;

String stringInit();
String *sliceToString(char slice[]);

void stringAppendChar(String *str, char c);
void stringAppendSlice(String *str, char slice[]);
void stringRemoveOne(String *str);
StringError stringRemoveN(String *str, size_t n);
void stringDestroy(String str);

//! VarInt is the Mojang's variety, therefore it does not use zig-zag encoding.
//! VarLong is also a VarInt, just longer.
typedef struct {
  uint8_t bytes[VARINT_MAX];
  size_t  length;
} VarInt;

VarInt encodeVarInt(int32_t value);
int32_t decodeVarInt(VarInt varint);

typedef struct {
  uint8_t bytes[VARLONG_MAX];
  size_t  length;
} VarLong;

VarLong encodeVarLong(int64_t value);
int64_t decodeVarLong(VarLong varlong);

