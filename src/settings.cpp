#include "settings.h"

SettingsData::SettingsData(DynamicJsonDocument doc) noexcept {
  this->timeout_sleep = doc["timeout_sleep"];
  this->ssid_wifi = String(doc["ssid_wifi"]);
  this->raw_password = String(doc["raw_password"]);
}

DynamicJsonDocument SettingsData::get_dynamic_json_document() noexcept {
  DynamicJsonDocument doc(SETTINGS_MAX_MEMORY_ALLOCATION);

  doc["timeout_sleep"] = this->timeout_sleep;
  doc["ssid_wifi"] = this->ssid_wifi;
  doc["raw_password"] = this->raw_password;

  return doc;
}

void SettingsManager::serialize(SettingsData data) noexcept {
  auto doc = data.get_dynamic_json_document();

  this->_storage.get_raw_file().remove(SETTINGS_FILENAME);
  this->_storage.raw_open_file(SETTINGS_FILENAME);
  serializeJsonPretty(doc, this->_storage.get_raw_file());
  this->_storage.raw_close_file();
}

SettingsData SettingsManager::deserialize() noexcept {
  DynamicJsonDocument doc(SETTINGS_MAX_MEMORY_ALLOCATION);

  this->_storage.raw_open_file(SETTINGS_FILENAME);
  deserializeJson(doc, this->_storage.get_raw_file());
  this->_storage.raw_close_file();

  return SettingsData(doc);
}