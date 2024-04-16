#include <stdio.h>
#include <unity/unity.h>
#include <unity/unity_internals.h>

#include "types.h"

void setUp() {}
void tearDown() {}

void stringTest() {
  String *str = sliceToString("1");
  TEST_ASSERT_TRUE(strcmp(str->char_vec, "1"));
  stringFree(str);
}
void varIntTest() {
  VarInt v = encodeVarInt(127);
  int32_t res = decodeVarInt(v);
  char buff[256];
  snprintf(buff, 256, "res=%i", res);
  TEST_ASSERT_TRUE_MESSAGE(127 == res, buff);
}
void varLongTest() {
  VarLong v = encodeVarLong(18446744073709);
  int64_t res = decodeVarLong(v);
  char buff[256];
  snprintf(buff, 256, "res=%li", res);
  TEST_ASSERT_TRUE_MESSAGE(18446744073709, buff);

}

int main(){
  UNITY_BEGIN();
  RUN_TEST(stringTest);
  RUN_TEST(varIntTest);
  RUN_TEST(varLongTest);
  return UNITY_END();
}
