#include <Arduino.h>
#include "settings.h"

void setup() {
  Serial.begin(921600);
  while (!Serial) {}
}

void loop() {
  // TEST SDCARD
  Serial.println("TEST SDCARD START");
  auto sdcard = SDCard(4);
  sdcard.overwrite_file("test.txt", "test information");

  String buffer;
  sdcard.read_file("test.txt", buffer);

  Serial.println(buffer);
  Serial.println(buffer == "test information");
  Serial.println("TEST SDCARD END");

  // TEST SETTINGS
  Serial.println("TEST SETTINGS START");
  auto settings_manager = SettingsManager(sdcard);
  SettingsData data_for_save;
  data_for_save.raw_password = "test_password";
  data_for_save.ssid_wifi = "kvantwifi";
  data_for_save.timeout_sleep = 42;

  settings_manager.serialize(data_for_save);

  auto settings_from_sdcard = settings_manager.deserialize();

  Serial.println(settings_from_sdcard.raw_password);
  Serial.println("TEST SETTINGS ND");
}