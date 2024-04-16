#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "other.h"
#include "types.h"

String stringInit() {
  String str = malloc(sizeof(String));
  str.char_vec = malloc(sizeof(char)*32);
  str.char_vec_capacity = 32;
  str.char_vec_size = 0;
  return str;
}

String sliceToString(char slice[]) {
  String str = stringInit();
  stringAppendSlice(str, slice);
  return str;
}

void stringAppendChar(String *str, char c) {
  if(++str->char_vec_size == str->char_vec_capacity) {
    str->char_vec_capacity += 32;
    str->char_vec = realloc(str->char_vec, str->char_vec_capacity);
  }
  str->char_vec[str->char_vec_size] = c;
}

void stringAppendSlice(String *str, char vec[]) {
  for(size_t i = 0; i < strlen(vec); ++i){
    stringAppendChar(str, vec[i]);
  }
}

void stringCutOne(String *str) {
  if(--str->char_vec_size % 32 == 0) {
    str->char_vec_capacity -= 32;
    str->char_vec = realloc(str->char_vec, str->char_vec_capacity);
  }
}

StringError stringCutN(String *str, size_t n) {
  if(n > str->char_vec_size) {
    return tried_to_remove_too_much;
  }
  
  for(size_t m = n; m > 0; --m){
    stringCutOne(str);
  }

  return none;
}

void stringDestroy(String str) {
  free(str.char_vec);
}

void freadToStringStruct(file *fptr, String *str) {
   char c;
   while((c = fgetc(fptr)) != -1) {
     stringAppendChar(str, c);
   }
}

VarInt encodeVarInt(int32_t value) {
  VarInt ret = {0};
  
  int32_t temp = 0;
  
  do {
     temp = value & 0b01111111;
     value >>= 7;
     
     if(value != 0) {
      temp |= 0b10000000;
     }

     ret.bytes[ret.length++] = temp;
  } while (value != 0);
  return ret;
}

int32_t decodeVarInt(VarInt varint) {
  int32_t decoded_value = 0;
  int32_t shift = 0;
  int32_t temp = 0;

  uint8_t byte = 0;

  for(size_t i = 0; i < varint.length; ++i){
    byte = varint.bytes[i];
    temp = byte & 0b01111111;
    decoded_value |= temp << shift;
    shift += 7;

    if((byte & 0b10000000) == 0) {
      break;
    }
  }

  return decoded_value;
}

VarLong encodeVarLong(int64_t value) {
  VarLong ret = {0};
  
  int32_t temp;

  do {
    temp = value & 0b01111111;
    value >>= 7;

    if(value != 0 || (ret.length++ < VARLONG_MAX -1 && (temp & 0b01000000) != 0)) {
      temp |= 0b10000000;
    }
    ret.bytes[ret.length] = temp;

  } while(value != 0);

  return ret;
}

int64_t decodeVarLong(VarLong varlong) {
  int64_t decoded_value = 0;
  int32_t shift = 0;
  
  int32_t temp = 0;

  uint8_t byte = 0;

  for(size_t i = 0; i < varlong.length; ++i) {
    byte = varlong.bytes[i];
    temp = byte & 0b01111111;
    decoded_value |= (int64_t)temp << shift;
    shift += 7;

    if((byte & 0b10000000) == 0) {
      break;
    }
  }

  return decoded_value;
}
