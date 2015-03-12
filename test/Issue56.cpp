// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

TEST(Issue56, UseStringAsKeyOfAnObject_Syntax1) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "key";

  o[s] = "value";
  ASSERT_STREQ("value", o[s]);

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":\"value\"}", json);
}

TEST(Issue56, AddStringAsKeyOfAnObject_Syntax2) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "key";

  o.add(s, "value");
  ASSERT_STREQ("value", o.at(s));

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":\"value\"}", json);
}

TEST(Issue56, AddStringAsKeyOfANestedArray_Syntax2) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "key";

  JsonArray& a = o.createNestedArray(s);
  ASSERT_EQ(&a, &o.at(s).asArray());

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":[]}", json);
}

TEST(Issue56, AddStringAsKeyOfANestedObject_Syntax2) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String s = "key";

  JsonObject& no = o.createNestedObject(s);
  ASSERT_EQ(&no, &o.at(s).asObject());

  char json[128];
  o.printTo(json, sizeof(json));
  ASSERT_STREQ("{\"key\":{}}", json);
}

TEST(Issue56, RemoveKey) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& o = jsonBuffer.createObject();
  String key = "key";

  o.add("key", "value");
  ASSERT_TRUE(o.containsKey("key"));

  o.remove(key);
  ASSERT_FALSE(o.containsKey("key"));
}
