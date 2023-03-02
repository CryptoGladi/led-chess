#include <Arduino.h>
#include "settings.h"

void setup() {
  Serial.begin(921600);
}

void loop() {
  // TEST SDCARD
  auto sdcard = SDCard(23);
  sdcard.overwrite_file("test.txt", "test information");

  String buffer;
  sdcard.read_file("test.txt", buffer);

  Serial.println(buffer);
  Serial.println(buffer == "test information");

  // TEST SETTINGS
  auto settings_manager = SettingsManager(sdcard);
  SettingsData data_for_save;
  data_for_save.raw_password = "test_password";
  data_for_save.ssid_wifi = "kvantwifi";
  data_for_save.timeout_sleep = 42;

  settings_manager.serialize(data_for_save);

  bool status;
  auto settings_from_sdcard = settings_manager.deserialize(status);

  Serial.println(settings_from_sdcard.raw_password);
  Serial.println(status);
}