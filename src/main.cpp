#include <Arduino.h>
#include "settings.h"

void setup() {
  Serial.begin(921600);
  while (!Serial) {}
}

void loop() {
  // TEST SDCARD
  /*
  Serial.println("TEST SDCARD START");
  auto sdcard = SDCard(4);
  sdcard.overwrite_file("test.txt", "test information");

  String buffer;
  sdcard.read_file("test.txt", buffer);

  Serial.println(buffer);
  Serial.println(buffer == "test information");
  Serial.println(buffer.length());
  Serial.println("TEST SDCARD END");
  */

  // TEST SETTINGS
  auto sdcard = SDCard(4);
  Serial.println("TEST SETTINGS START");
  auto settings_manager = SettingsManager(sdcard);
  SettingsData data_for_save;
  data_for_save.raw_password = "test_password is my!";
  data_for_save.ssid_wifi = "kvantwifi";
  data_for_save.timeout_sleep = 42;

  Serial.println("TEST SETTINGS serialize");
  settings_manager.serialize(data_for_save);

  Serial.println("TEST SETTINGS deserialize");
  auto settings_from_sdcard = settings_manager.deserialize();

  Serial.println(settings_from_sdcard.raw_password);
  Serial.println(settings_from_sdcard.raw_password == data_for_save.raw_password);
  Serial.println("TEST SETTINGS END");
}