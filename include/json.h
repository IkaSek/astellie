/// json.h
/// this file provides a json parser and writer

#include <stdbool.h>
#include "types.h"

#pragma once

typedef struct Value {
  enum ValueOption {
    vo_as_int,
    vo_as_str,
    vo_as_bool,
    vo_as_array,
    vo_as_object,
  } value_option;

  union ValueUnion {
    size_t as_int;
    String as_str;
    bool as_bool;
  } value_union;
} Value;

typedef struct JSONNode {
  Optional(String) name;
  Optional(Value)  value;
  Vector(struct JSONNode) subnodes;
} JSONNode;

typedef struct {
  Vector(JSONNode) nodes;
  String buffer;
  
} JSON;
